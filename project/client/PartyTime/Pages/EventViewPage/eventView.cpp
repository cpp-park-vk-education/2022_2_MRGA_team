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
    date(new QLineEdit()), time(new QLineEdit()),
    address(new QLineEdit()), visitors(new QLineEdit()),
    maxVisitors(new QLineEdit())
{

    try {
        HttpConnector connector("contest.yandex.ru");
        auto res = connector.GET("/");
        std::cout << "result = " << res.result << std::endl;
            if (res.response) {
                std::cout << "has value" << res.response.has_value() << std::endl;
                std::cout << res.response->response_body << std::endl;
                std::cout << res.response->status.str << std::endl;
                for (auto&[h, v] : res.response->headers) {
                    std::cout << "header " << h << " value " << v << std::endl;
                }
            }
    } catch(std::exception& error) {
        std::cout << error.what() << std::endl;
    }

    this->createEventButton->setProperty("cssClass", "createEventButton");
//    this->createEventButton->setStyleSheet("min-width: 200px; min-height: 50px; background-color: #ffffff; color: #000000; border-radius: 5px;");
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

    connect(addButton, &QPushButton::clicked, this, &EventViewPage::onAdd);
    connect(closeFormButton, &QPushButton::clicked, this, &EventViewPage::onRemove);
    connect(createEventButton, &QPushButton::clicked, this, &EventViewPage::onCreate);
}

void EventViewPage::onAdd()
{
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

    QHBoxLayout* input1 = new QHBoxLayout();
    inputLayout->addLayout(input1, Qt::AlignTop);
    QLabel* eventNameLabel = new QLabel("Event name");
    input1->addWidget(eventNameLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    input1->addWidget(eventName, 4, Qt::AlignLeft | Qt::AlignTop);

    eventNameLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    eventName->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    QHBoxLayout* input2 = new QHBoxLayout();
    inputLayout->addLayout(input2, Qt::AlignTop);

    QLabel* descriptionLabel = new QLabel("Description");
    input2->addWidget(descriptionLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    input2->addWidget(description, 4, Qt::AlignLeft | Qt::AlignTop);

    descriptionLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    description->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    QHBoxLayout* input3 = new QHBoxLayout();
    inputLayout->addLayout(input3, Qt::AlignTop);

    QLabel* dateLabel = new QLabel("Date");
    input3->addWidget(dateLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    input3->addWidget(date, 4, Qt::AlignLeft | Qt::AlignTop);

    dateLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    date->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");


    QHBoxLayout* input4 = new QHBoxLayout();
    inputLayout->addLayout(input4, Qt::AlignTop);

    QLabel* timeLabel = new QLabel("Time");
    input4->addWidget(timeLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    input4->addWidget(time, 4, Qt::AlignLeft | Qt::AlignTop);

    timeLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    time->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");


    QHBoxLayout* input5 = new QHBoxLayout();
    inputLayout->addLayout(input5, Qt::AlignTop);

    QLabel* addressLabel = new QLabel("Address");
    input5->addWidget(addressLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    input5->addWidget(address, 4, Qt::AlignLeft | Qt::AlignTop);

    addressLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    address->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");


    QHBoxLayout* input6 = new QHBoxLayout();
    inputLayout->addLayout(input6, Qt::AlignTop);

    QLabel* visitorsLabel = new QLabel("People");
    input6->addWidget(visitorsLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    input6->addWidget(visitors, 4, Qt::AlignLeft | Qt::AlignTop);

    visitorsLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    visitors->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");


    QHBoxLayout* input7 = new QHBoxLayout();
    inputLayout->addLayout(input7, Qt::AlignTop);

    QLabel* maxVisitorsLabel = new QLabel("Maximum visitors");
    input7->addWidget(maxVisitorsLabel, 1,  Qt::AlignLeft | Qt::AlignTop);
    input7->addWidget(maxVisitors, 4, Qt::AlignLeft | Qt::AlignTop);

    maxVisitorsLabel->setStyleSheet("min-width: 200px; margin-top: 10px; color: #000000; font-size: 20px; font-weigth: 400;");
    maxVisitors->setStyleSheet("color: #000000; min-height: 30px; min-width: 600px; font-size: 20px; font-weight: 300;");

    inputLayout->addWidget(this->createEventButton, Qt::AlignTop | Qt::AlignCenter);
    form->show();
}

void EventViewPage::onRemove()
{
    form->hide();
    this->eventName->clear();
    this->description->clear();
    this->date->clear();
    this->time->clear();
    this->address->clear();
    this->visitors->clear();
    this->maxVisitors->clear();
}

void EventViewPage::onCreate()
{
    this->eventList->addEvent({this->description->text(),
                                   this->eventName->text(),
                                   this->visitors->text(),
                                   this->maxVisitors->text(),
                                   this->date->text(),
                                   this->time->text(),
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
        if (elem == "") {

        }
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
