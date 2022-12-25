#include "eventView.hpp"

#include <QLabel>
#include <QToolBar>
#include <QBoxLayout>
#include <QAction>
#include <iostream>
#include <QWidget>
#include <iostream>

EventViewPage::EventViewPage(QWidget *parent) : painter(parent), mainLayout(new QVBoxLayout(this)),
    addButton(new QPushButton()),
    closeFormButton(new QPushButton()), createEventButton(new QPushButton("Create")),
    eventName(new QLineEdit), description(new QLineEdit()),
    date(new QDateEdit()), time(new QTimeEdit()),
    address(new QLineEdit()),
//    visitors(new QLineEdit()),
    maxVisitors(new QLineEdit()),
    party(PartyTimeConnector::default_implementation("0.0.0.0", "8081"))
{
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

    // Form
//    form1 = new EventForm("createFormInput", 6, "createFormButton", 1, this);
//    QVBoxLayout* formLayout = new QVBoxLayout(form1);
//    formLayout->setAlignment(Qt::AlignCenter);
//    form1->hide();

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
}

// всплытие формы
void EventViewPage::onAdd()
{
    form->show();
//    form1->show();
}

void EventViewPage::onRemove()
{
    if (form) { // form
        form->hide();
        this->eventName->clear();
        this->description->clear();
        this->date->clear();
        this->time->clear();
        this->address->clear();
//        this->visitors->clear();
        this->maxVisitors->clear();
    }
}

void EventViewPage::onCreate()
{
    party->events.get();
    Event event{eventName->text().toStdString(),
                    this->date->date().toString().toStdString() + " " + this->time->time().toString().toStdString(),
                    0, Address{this->address->text().toStdString(), 0},
                    this->description->text().toStdString(),
                    this->maxVisitors->text().toInt(),
//                    this->visitors->text().toInt(), 0
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

    std::cout << event.toJSON() << std::endl;

    // createEvent
    auto resultat = party->events->create_event(event);
    if (!resultat.body.has_value()) {
        std::cout << resultat.result.message() << std::endl;
        QMessageBox errorForm;
        errorForm.setText(QString::fromStdString(resultat.result.message()));
        errorForm.exec();
//        form1->hide();
        form->hide();
        this->eventName->clear();
        this->description->clear();
        this->date->clear();
        this->time->clear();
        this->address->clear();
//        this->visitors->clear();
        this->maxVisitors->clear();
        return;
    }

    this->eventList->addEvent({this->description->text(),
                                   this->eventName->text(),
//                                   this->visitors->text(),
                                    "0",
                                   this->maxVisitors->text(),
                                   this->date->date().toString(),
                                   this->time->time().toString(),
                                   this->address->text()});

    form->hide();
//    form1->hide();
    this->eventName->clear();
    this->description->clear();
    this->date->clear();
    this->time->clear();
    this->address->clear();
//    this->visitors->clear();
    this->maxVisitors->clear();
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


void EventViewPage::showMyEvents()
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
        eventList->addEvent(new EventItem("visitor", ev.description,
                                          ev.title,
                                          ev.curr_visitors,
                                          *ev.max_visitors,
                                          getDate(ev.date_time),
                                          getTime(ev.date_time),
                                          ev.address.address));
    }
}
