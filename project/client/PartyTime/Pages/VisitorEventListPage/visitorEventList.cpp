#include "visitorEventList.hpp"
#include <iostream>

VisitorEventListPage::VisitorEventListPage(QWidget *parent) : painter(parent), mainLayout(new QVBoxLayout(this)), comboBox(new QComboBox(this)),
    hideButton(new QPushButton("Search", this)),
    lineEdit(new QLineEdit(this)), party(PartyTimeConnector::default_implementation("0.0.0.0", "8081"))
{
    // задаем id страницы
    this->setObjectName("visitorPage");

    // создаем фабрики
    Navbar* navbarFactory = new Navbar("", 3);
    this->navbar = *navbarFactory->create("visitor");
    this->navbar.setGeometry(this->x(), this->y(), 1440, 100);

    // DropDownMenu
    QGridLayout *comboBoxLayout = new QGridLayout(this);
    comboBoxLayout->setContentsMargins(30, 0, 25, 0);
    comboBox->setObjectName("eventCategories");

    hideButton->setProperty("cssClass", "searchButton");
    hideButton->setFixedWidth(200);

    QPalette pal = lineEdit->palette();
    pal.setColor(QPalette::PlaceholderText, QColor(0, 0, 0, 100));
    lineEdit->setMaximumWidth(800);
    lineEdit->setProperty("cssClass", "comboBoxEdit");
    lineEdit->setPalette(pal);
    lineEdit->setPlaceholderText("Event name");
    lineEdit->setFont(QFont("Times", -1, QFont::Bold));
    lineEdit->setStyleSheet("padding: 10px; background-color: #babfd9; color: #fff; border-radius: 15px");


    comboBoxLayout->addWidget(comboBox, 0, 0, 1, 2);
    comboBoxLayout->addWidget(hideButton, 0, 1, 1, 1);
    comboBoxLayout->addWidget(lineEdit, 0, 2, 1, 1);

    listView = new QListView(comboBox);
    listView->setStyleSheet("QListView::item {                              \
                             margin-bottom: 10px; color: #ffffff; border-bottom: 2px solid white; font-size: 16px;}  \
                             QListView::item:selected {                     \
                             border-bottom: 2px solid rgba(164, 115, 18, 1);    \
                             color: rgba(164, 115, 18, 1); font-size: 16px;}                                \
                             QListView::item:checked {                      \
                             margin-bottom: 30px; background-color: green;                       \
                             color: green; font-size: 16px;}"
                             );

    comboBox->setProperty("cssClaas", "comboBoxList");
    comboBox->setFixedWidth(250);
    comboBox->setView(listView);
    comboBox->addItem("All events");
    comboBox->addItem("Subscribe events");
    comboBox->addItem("Closest events");

    std::cout << "ComboBox text: " << comboBox->currentText().toStdString() << std::endl;

    connect(hideButton, &QPushButton::clicked, this, &VisitorEventListPage::hideRow);

    mainLayout->addWidget(&this->navbar, 0, Qt::AlignCenter | Qt::AlignTop);
    mainLayout->addLayout(comboBoxLayout, Qt::AlignTop | Qt::AlignCenter);
    this->eventList = new EventList("visitor", 0);

    // GetEvent
    updateEvents();
    mainLayout->addWidget(this->eventList, 2, Qt::AlignTop | Qt::AlignCenter);

    connect(this->eventList, &EventList::subscribeEvent, this, &VisitorEventListPage::subsrcibeHandler);
    connect(this->eventList, &EventList::leaveOnEvent, this, &VisitorEventListPage::leaveEventHandler);
}

VisitorEventListPage::VisitorEventListPage(const std::initializer_list<QString> typesList) : mainLayout(new QVBoxLayout())
{
    for (const auto& elem : typesList) {
        if (elem == "") {

        }
    }
}

VisitorEventListPage::VisitorEventListPage(const QString &headerType, const QString &navbarType,
                                           const QString &eventListType, const QString &footerType) : mainLayout(new QVBoxLayout())
{
    this->setObjectName("visitorPage");

    Header* headerFactory = new Header();
    this->header = *(headerFactory->create(headerType));
    delete headerFactory;
    headerFactory = nullptr;

    Navbar* navbarFactory = new Navbar("", 3);
    this->navbar.setGeometry(this->x(), this->y(), 1440, 100);
    this->navbar = *(navbarFactory->create(navbarType));
    mainLayout->addWidget(&this->navbar, 0, Qt::AlignCenter | Qt::AlignTop);
    delete navbarFactory;
    navbarFactory = nullptr;

    EventList* eventListFactory = new EventList("visitor", 0);
    this->eventList = (eventListFactory->create(eventListType));
    delete eventListFactory;
    eventListFactory = nullptr;
    updateEvents();
    mainLayout->addWidget(this->eventList, 2, Qt::AlignTop | Qt::AlignCenter);

    Footer* footerFactory = new Footer();
    this->footer = *(footerFactory->create(footerType));
    delete footerFactory;
    footerFactory = nullptr;
}

VisitorEventListPage::~VisitorEventListPage()
{

}

std::string VisitorEventListPage::getDate(const std::string &dateTime)
{
    return {dateTime.begin(), dateTime.begin() + dateTime.find(' ')};
}

std::string VisitorEventListPage::getTime(const std::string &dateTime)
{
    return {dateTime.begin() + dateTime.find(' ') + 1,  dateTime.end()};
}

void VisitorEventListPage::hideRow()
{
    std::vector<std::string> headers;
}

void VisitorEventListPage::updateEvents()
{
    auto resultat = party->events->events();

    if (!resultat.body.has_value()) {
        std::cout << resultat.result.message() << std::endl;
        QMessageBox errorForm;
        errorForm.setText(QString::fromStdString(resultat.result.message()));
        errorForm.exec();
        return;
    }

    auto events = *resultat.body;
    for (auto & ev: events) {
        std::cout << "Event id" << ev.id << std::endl;
        eventList->addEvent(new EventItem(ev.id, "visitor", ev.description,
                                          ev.title,
                                          ev.curr_visitors,
                                          *ev.max_visitors,
                                          getDate(ev.date_time),
                                          getTime(ev.date_time),
                                          ev.address.address));
    }

}

void VisitorEventListPage::subsrcibeHandler(unsigned int _eventId)
{
    if (_eventId == 0) {
        auto resultat = party->events->events();

        if (!resultat.body.has_value()) {
            std::cout << resultat.result.message() << std::endl;
            QMessageBox errorForm;
            errorForm.setText(QString::fromStdString(resultat.result.message()));
            errorForm.exec();
            return;
        }

        auto events = *resultat.body;


        // TODO: после отправки запроса, что на event подписались получаем обновленный event
        // вызываем updateEvents();
        EventItem* editEvent = this->eventList->getEvent(_eventId);

        // обновленная структура
//       {            editEvent->getEventName()->text().toStdString();
//                    editEvent->getDescription()->text().toStdString();
//                    editEvent->getDate()->text().toStdString();
//                    editEvent->getTime()->text().toStdString();
//                    editEvent->getAddress()->text().toStdString();
//                    editEvent->getMaxVisitors()->text().toStdString();
//        }

        std::cout << editEvent->getEventName()->text().toStdString() << std::endl;
        std::cout << editEvent->getDescription()->text().toStdString() << std::endl;
        std::cout << editEvent->getDate()->text().toStdString() << std::endl;
        std::cout << editEvent->getTime()->text().toStdString() << std::endl;
        std::cout << editEvent->getAddress()->text().toStdString() << std::endl;
        std::cout << editEvent->getMaxVisitors()->text().toStdString() << std::endl;
    }

    // TODO: отправка запроса о подписке на ивент
    std::cout << "SUBSCRIBE EVENT" << std::endl;
}

void VisitorEventListPage::leaveEventHandler(unsigned int _eventId)
{
    if (_eventId == 0) {
            auto resultat = party->events->events();

            if (!resultat.body.has_value()) {
                std::cout << resultat.result.message() << std::endl;
                QMessageBox errorForm;
                errorForm.setText(QString::fromStdString(resultat.result.message()));
                errorForm.exec();
                return;
            }

            auto events = *resultat.body;


            // TODO: после отправки запроса, что на event подписались получаем обновленный event
            // вызываем updateEvents();
            EventItem* editEvent = this->eventList->getEvent(_eventId);

            // обновленная структура
    //       {            editEvent->getEventName()->text().toStdString();
    //                    editEvent->getDescription()->text().toStdString();
    //                    editEvent->getDate()->text().toStdString();
    //                    editEvent->getTime()->text().toStdString();
    //                    editEvent->getAddress()->text().toStdString();
    //                    editEvent->getMaxVisitors()->text().toStdString();
    //        }

            std::cout << editEvent->getEventName()->text().toStdString() << std::endl;
            std::cout << editEvent->getDescription()->text().toStdString() << std::endl;
            std::cout << editEvent->getDate()->text().toStdString() << std::endl;
            std::cout << editEvent->getTime()->text().toStdString() << std::endl;
            std::cout << editEvent->getAddress()->text().toStdString() << std::endl;
            std::cout << editEvent->getMaxVisitors()->text().toStdString() << std::endl;
        }

    // TODO: отправка запроса об отписке с ивента
    std::cout << "LEAVE EVENT" << std::endl;
}
