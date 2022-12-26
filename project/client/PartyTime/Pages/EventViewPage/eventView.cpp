#include "eventView.hpp"

#include <QLabel>
#include <QToolBar>
#include <QBoxLayout>
#include <QAction>
#include <iostream>
#include <QWidget>
#include <iostream>

#include <typeinfo>

EventViewPage::EventViewPage(QWidget *parent) : painter(parent), mainLayout(new QVBoxLayout(this)),
    addButton(new QPushButton()),
    closeFormButton(new QPushButton()), createEventButton(new QPushButton("Create")),
    eventName(new QLineEdit), description(new QLineEdit()),
    date(new QDateEdit()), time(new QTimeEdit()),
    address(new QLineEdit()),
//    visitors(new QLineEdit()),
    maxVisitors(new QLineEdit()), curEventId(0),
    party(PartyTimeConnector::default_implementation("0.0.0.0", "8081"))
{
    // стлизация edit-ов
    eventName->setProperty("cssClass", "createFormInput");
    description->setProperty("cssClass", "createFormInput");
    date->setProperty("cssClass", "createFormInput");
    time->setProperty("cssClass", "createFormInput");
    address->setProperty("cssClass", "createFormInput");
    maxVisitors->setProperty("cssClass", "createFormInput");

    this->createEventButton->setProperty("cssClass", "createEventButton");
    this->setContentsMargins(0, 20, 0, 0);
    Navbar* navbarFactory = new Navbar("", 3);
    this->navbar = *navbarFactory->create("visitor");
    this->navbar.setGeometry(this->x(), this->y(), 1440, 100);
    this->navbar.setStyleSheet(this->navbar.styleSheet() + "max-height: 100px;");
    mainLayout->addWidget(&this->navbar, 0, Qt::AlignTop | Qt::AlignCenter);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setContentsMargins(25, 0, 0, 0);
    addButton->setProperty("cssClass", "addButton");
    closeFormButton->setProperty("cssClass", "deleteEventBtn");
    buttonLayout->addWidget(addButton, 0, Qt::AlignLeft | Qt::AlignTop);
    buttonLayout->addWidget(closeFormButton, 1, Qt::AlignLeft | Qt::AlignTop);

    mainLayout->addLayout(buttonLayout, Qt::AlignTop | Qt::AlignLeft);

    this->eventList = new EventList("organizer", 0);
    mainLayout->addWidget(eventList, 2, Qt::AlignTop | Qt::AlignCenter);

    // Forms
//    form1 = new EventForm("createFormInput", 6, "createFormButton", 1, this);
//    QVBoxLayout* formLayout = new QVBoxLayout(form1);
//    formLayout->setAlignment(Qt::AlignCenter);
//    form1->hide();

    // Create form
    form = new painter(this);
    form->setProperty("cssClass", "formEvent");
    form->setGeometry(300, 300, 1000, 600);
    QVBoxLayout* formLayout = new QVBoxLayout(form);

    QLabel* formTitle = new QLabel("New event");
    formTitle->setContentsMargins(0, 0, 0, 20);
    formTitle->setStyleSheet("color: #000000; font-size: 28px; font-weight: 900");
    formLayout->addWidget(formTitle, 1, Qt::AlignTop | Qt::AlignCenter);

    QVBoxLayout* inputLayout = new QVBoxLayout();
    inputLayout->setContentsMargins(70, 0, 0, 0);
    formLayout->addLayout(inputLayout, Qt::AlignTop);
    formLayout->setSpacing(0);

    QHBoxLayout* inputTitle = new QHBoxLayout();
    inputLayout->addLayout(inputTitle, Qt::AlignTop);
    QLabel* eventNameLabel = new QLabel("Event name");
    inputTitle->addWidget(eventNameLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputTitle->addWidget(eventName, 4, Qt::AlignLeft | Qt::AlignTop);

    eventNameLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weight: 900;");
    eventName->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    QHBoxLayout* inputDescription = new QHBoxLayout();
    inputLayout->addLayout(inputDescription, Qt::AlignTop);
    QLabel* descriptionLabel = new QLabel("Description");
    inputDescription->addWidget(descriptionLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputDescription->addWidget(description, 4, Qt::AlignLeft | Qt::AlignTop);

    descriptionLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weight: 900;");
    description->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    QHBoxLayout* inputDate = new QHBoxLayout();
    inputLayout->addLayout(inputDate, Qt::AlignTop);

    QLabel* dateLabel = new QLabel("Date");
    inputDate->addWidget(dateLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputDate->addWidget(date, 4, Qt::AlignLeft | Qt::AlignTop);
    date->setDate(QDate(2022, 12, 22));

    dateLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weight: 900;");
    date->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    QHBoxLayout* inputTime = new QHBoxLayout();
    inputLayout->addLayout(inputTime, Qt::AlignTop);

    QLabel* timeLabel = new QLabel("Time");
    inputTime->addWidget(timeLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputTime->addWidget(time, 4, Qt::AlignLeft | Qt::AlignTop);

    timeLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weight: 900;");
    time->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    QHBoxLayout* inputAddress = new QHBoxLayout();
    inputLayout->addLayout(inputAddress, Qt::AlignTop);

    QLabel* addressLabel = new QLabel("Address");
    inputAddress->addWidget(addressLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputAddress->addWidget(address, 4, Qt::AlignLeft | Qt::AlignTop);

    addressLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weight: 900;");
    address->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    QHBoxLayout* inputMaxVisitors = new QHBoxLayout();
    inputLayout->addLayout(inputMaxVisitors, Qt::AlignTop);

    QLabel* maxVisitorsLabel = new QLabel("Maximum visitors");
    inputMaxVisitors->addWidget(maxVisitorsLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputMaxVisitors->addWidget(maxVisitors, 4, Qt::AlignLeft | Qt::AlignTop);

    maxVisitorsLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weight: 900;");
    maxVisitors->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    inputLayout->addWidget(this->createEventButton, Qt::AlignTop | Qt::AlignCenter);
    form->hide();

    connect(addButton, &QPushButton::clicked, this, &EventViewPage::onAdd);
    connect(closeFormButton, &QPushButton::clicked, this, &EventViewPage::onRemove);
    connect(createEventButton, &QPushButton::clicked, this, &EventViewPage::onCreate);
    connect(this->eventList, &EventList::openEditForm, this, &EventViewPage::onEdit);

    loadEvents();
}

// всплытие формы
void EventViewPage::onAdd()
{
    this->cleanForm();
    createEventButton->setText("Create");
    form->show();
}

void EventViewPage::onRemove()
{
    if (form) { // form
        form->hide();
    }
}

void EventViewPage::onCreate()
{
    if (createEventButton->text() == "Create") {

        unsigned int curUserId = QString::fromStdString(party->auth->id()).toUInt();
        // std::cout << "curUserId: " << curUserId << std::endl;
        // std::cout << "party auth: " << party->auth->id() << std::endl;

        Event event{eventName->text().toStdString(),
                        this->date->date().toString().toStdString() + " " + this->time->time().toString().toStdString(),
                        curUserId, Address{this->address->text().toStdString(), 0},
                        this->description->text().toStdString(),
                        this->maxVisitors->text().toInt(),
                        0, 0
                   };

        if (event.description == "" || event.title == "" ||
                event.date_time == "" || event.address.address == "" ||
                this->maxVisitors->text().toStdString() == "") {
            QMessageBox errorForm;
            errorForm.setText("All fields must be filled");
            errorForm.exec();
            return;
        }

        // std::cout << event.toJSON() << std::endl;

        // createEvent
        auto resultat = party->events->create_event(event);

        if (!resultat.body.has_value()) {
            std::cout << resultat.result.message() << std::endl;
            QMessageBox errorForm;
            errorForm.setText(QString::fromStdString(resultat.result.message()));
            errorForm.exec();

            form->hide();
            return;
        }

//        std::cout << "Id user-a: " << resultat.body->user_id << std::endl;
//        std::cout << "Id event-a: " << resultat.body->id << std::endl;

        this->eventList->addEvent(resultat.body->id, {this->description->text(),
                                       this->eventName->text(),
                                        QString::number(curUserId),
                                       this->maxVisitors->text(),
                                       this->date->date().toString(),
                                       this->time->time().toString(),
                                       this->address->text()});
    } else {
        // TODO: обновить event
        EventItem* editEvent = this->eventList->getEvent(this->curEventId);

        editEvent->updateState(this->description->text().toStdString(),
                               this->eventName->text().toStdString(),
                               0,
                               this->maxVisitors->text().toUInt(),
                               this->date->text().toStdString(),
                               this->time->text().toStdString(),
                               this->address->text().toStdString()
                               );

        // std::cout << "AFTER UPDATE" << std::endl;
        // std::cout << editEvent->getEventName()->text().toStdString() << std::endl;
        // std::cout << editEvent->getDescription()->text().toStdString() << std::endl;
        // std::cout << editEvent->getDate()->text().toStdString() << std::endl;
        // std::cout << editEvent->getTime()->text().toStdString() << std::endl;
        // std::cout << editEvent->getAddress()->text().toStdString() << std::endl;
        // std::cout << editEvent->getMaxVisitors()->text().toStdString() << std::endl;

        editEvent->repaint();
    }

    form->hide();
}

void EventViewPage::onEdit(const unsigned int& _eventId)
{
    this->curEventId = _eventId;
    createEventButton->setText("Save");

    // Редактируем конкретный event
    EventItem* editEvent = this->eventList->getEvent(_eventId);

    // устанавливаем в форме текст, который находится в конкретных EventItem-ах
    this->eventName->setText(editEvent->getEventName()->text());
    this->description->setText(editEvent->getDescription()->text());
    this->date->setDate(QDate::fromString(editEvent->getDate()->text()));
    this->time->setTime(QTime::fromString(editEvent->getTime()->text()));
    this->address->setText(editEvent->getAddress()->text());
    auto pos = editEvent->getMaxVisitors()->text().toStdString().find(":") + 1;
    QString stringMaxVisitors = QString::fromStdString(editEvent->getMaxVisitors()->text().toStdString().substr(pos));
    this->maxVisitors->setText(stringMaxVisitors);

    form->show();

    std::cout << "BEFORE UPDATE" << std::endl;
    std::cout << editEvent->getEventName()->text().toStdString() << std::endl;
    std::cout << editEvent->getDescription()->text().toStdString() << std::endl;
    std::cout << editEvent->getDate()->text().toStdString() << std::endl;
    std::cout << editEvent->getTime()->text().toStdString() << std::endl;
    std::cout << editEvent->getAddress()->text().toStdString() << std::endl;
    std::cout << editEvent->getMaxVisitors()->text().toStdString() << std::endl;
}

EventViewPage::EventViewPage(const std::initializer_list<QString> typesList) : mainLayout(new QVBoxLayout())
{
    for (const auto& elem : typesList) {
        if (elem == "") {}
    }
}

EventViewPage::EventViewPage(const QString &headerType, const QString &navbarType, const QString &eventListType, const QString &footerType) : mainLayout(new QVBoxLayout())
{
    Header* headerFactory = new Header();
    this->header = *(headerFactory->create(headerType));
    delete headerFactory;
    headerFactory = nullptr;

    Navbar* navbarFactory = new Navbar();
    this->navbar = *(navbarFactory->create(navbarType));
    delete navbarFactory;
    navbarFactory = nullptr;

    EventList* eventListFactory = new EventList();
    this->eventList = (eventListFactory->create(eventListType));
    delete eventListFactory;
    eventListFactory = nullptr;

    Footer* footerFactory = new Footer();
    this->footer = *(footerFactory->create(footerType));
    delete footerFactory;
    footerFactory = nullptr;
}

EventViewPage::~EventViewPage()
{
    delete mainLayout;
}

std::string EventViewPage::getDate(const std::string &dateTime)
{
    return {dateTime.begin(), dateTime.begin() + dateTime.find(' ')};
}

std::string EventViewPage::getTime(const std::string &dateTime)
{
    return {dateTime.begin() + dateTime.find(' ') + 1,  dateTime.end()};
}



void EventViewPage::loadEvents()
{
    auto resultat = party->events->events();

    if (!resultat.body.has_value()) {
        std::cout << resultat.result.message() << std::endl;
        QMessageBox errorForm;
        errorForm.setText(QString::fromStdString(resultat.result.message()));
        errorForm.exec();
        return;
    }

    // TODO: добавить все мои event-ы в EventList

//    for (auto & ev: events) {
//        eventList->addEvent(new EventItem(ev.id, "visitor", ev.description,
//                                          ev.title,
//                                          ev.curr_visitors,
//                                          *ev.max_visitors,
//                                          getDate(ev.date_time),
//                                          getTime(ev.date_time),
//                                          ev.address.address));
//    }

    auto events = *resultat.body;
    for (auto & ev: events) {
        std::cout << "EVENT ID: " << ev.id << std::endl;
        std::cout << "USER ID: " << ev.user_id << std::endl;
        // тут надо будет копировать event-ы а не создававать
        eventList->addEvent(new EventItem(ev.id, "visitor", ev.description,
                                          ev.title,
                                          ev.curr_visitors,
                                          *ev.max_visitors,
                                          getDate(ev.date_time),
                                          getTime(ev.date_time),
                                          ev.address.address));

        eventList->getEvent(ev.id)->setSubcribeButtonText("Edit");
    }

}




void EventViewPage::cleanForm()
{
    this->eventName->clear();
    this->description->clear();
    this->date->clear();
    this->date->setDate(QDate(2022, 12, 22));
    this->time->clear();
    this->time->setTime(QTime(0, 0, 0));
    this->address->clear();
    this->maxVisitors->clear();
}
