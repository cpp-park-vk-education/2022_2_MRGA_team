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
    address(new QLineEdit()), visitors(new QLineEdit()),
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
    form = new painter(this);
    form->setProperty("cssClass", "formEvent");
    form->setGeometry(300, 300, 1000, 600);
    QVBoxLayout* formLayout = new QVBoxLayout(form);

    QLabel* formTitle = new QLabel("New event");
    formTitle->setContentsMargins(0, 0, 0, 20);
    form->setStyleSheet("color: #000000; font-size: 28px; font-weight: 900");
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

    eventNameLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    eventName->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    QHBoxLayout* inputDescription = new QHBoxLayout();
    inputLayout->addLayout(inputDescription, Qt::AlignTop);

    QLabel* descriptionLabel = new QLabel("Description");
    inputDescription->addWidget(descriptionLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputDescription->addWidget(description, 4, Qt::AlignLeft | Qt::AlignTop);

    descriptionLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    description->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    QHBoxLayout* inputDate = new QHBoxLayout();
    inputLayout->addLayout(inputDate, Qt::AlignTop);

    QLabel* dateLabel = new QLabel("Date");
    inputDate->addWidget(dateLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputDate->addWidget(date, 4, Qt::AlignLeft | Qt::AlignTop);

    dateLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    date->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");


    QHBoxLayout* inputTime = new QHBoxLayout();
    inputLayout->addLayout(inputTime, Qt::AlignTop);

    QLabel* timeLabel = new QLabel("Time");
    inputTime->addWidget(timeLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputTime->addWidget(time, 4, Qt::AlignLeft | Qt::AlignTop);

    timeLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    time->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");


    QHBoxLayout* inputAddress = new QHBoxLayout();
    inputLayout->addLayout(inputAddress, Qt::AlignTop);

    QLabel* addressLabel = new QLabel("Address");
    inputAddress->addWidget(addressLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputAddress->addWidget(address, 4, Qt::AlignLeft | Qt::AlignTop);

    addressLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    address->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    QHBoxLayout* inputVisitors = new QHBoxLayout();
    inputLayout->addLayout(inputVisitors, Qt::AlignTop);

    QLabel* visitorsLabel = new QLabel("People");
    inputVisitors->addWidget(visitorsLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputVisitors->addWidget(visitors, 4, Qt::AlignLeft | Qt::AlignTop);

    visitorsLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    visitors->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    QHBoxLayout* inputMaxVisitors = new QHBoxLayout();
    inputLayout->addLayout(inputMaxVisitors, Qt::AlignTop);

    QLabel* maxVisitorsLabel = new QLabel("Maximum visitors");
    inputMaxVisitors->addWidget(maxVisitorsLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    inputMaxVisitors->addWidget(maxVisitors, 4, Qt::AlignLeft | Qt::AlignTop);

    maxVisitorsLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
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
}

void EventViewPage::onRemove()
{
    if (form) {
        form->hide();
        this->eventName->clear();
        this->description->clear();
        this->date->clear();
        this->time->clear();
        this->address->clear();
        this->visitors->clear();
        this->maxVisitors->clear();
    }
}

void EventViewPage::onCreate()
{
    Event event{eventName->text().toStdString(),
                    this->date->date().toString().toStdString() + " " + this->time->time().toString().toStdString(),
                    0, Address{this->address->text().toStdString(), 0},
                    this->description->text().toStdString(),
                    this->maxVisitors->text().toInt(),
                    this->visitors->text().toInt(), 0};

    if (event.description == "" || event.title == "" ||
            event.date_time == "" || event.address.address == "" ||
            this->maxVisitors->text().toStdString() == "" || this->visitors->text().toStdString() == "") {
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
        form->hide();
        return;
    }

    this->eventList->addEvent({this->description->text(),
                                   this->eventName->text(),
                                   this->visitors->text(),
                                   this->maxVisitors->text(),
                                   this->date->date().toString(),
                                   this->time->time().toString(),
                                   this->address->text()});

    form->hide();
    this->eventName->clear();
    this->description->clear();
    this->date->clear();
    this->time->clear();
    this->address->clear();
    this->visitors->clear();
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
