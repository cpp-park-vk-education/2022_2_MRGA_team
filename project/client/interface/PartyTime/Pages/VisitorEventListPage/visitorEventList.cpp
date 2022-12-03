#include "visitorEventList.hpp"
#include <iostream>

VisitorEventListPage::VisitorEventListPage(QWidget *parent) : painter(parent), mainLayout(new QVBoxLayout(this))
{
    // задаем id страницы
    this->setObjectName("visitorPage");

    // создаем фабрики
    Navbar* navbarFactory = new Navbar("", 3);
    this->navbar = *navbarFactory->create("visitor");
    EventList* eventListFactory = new EventList();
    this->eventList = *eventListFactory->create("");

    mainLayout->addWidget(&this->navbar, 1, Qt::AlignTop);
    mainLayout->addWidget(&this->eventList, 2, Qt::AlignTop);
}

VisitorEventListPage::VisitorEventListPage(const std::initializer_list<QString> typesList) : mainLayout(new QVBoxLayout())
{
    for (const auto& elem : typesList) {
        if (elem == "") {

        }
    }
}

VisitorEventListPage::VisitorEventListPage(const QString &headerType, const QString &navbarType, const QString &eventListType, const QString &footerType) : mainLayout(new QVBoxLayout())
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
    this->eventList = *(eventListFactory->create(eventListType));
    delete eventListFactory;
    eventListFactory = nullptr;

    Footer* footerFactory = new Footer();
    this->footer = *(footerFactory->create(footerType));
    delete footerFactory;
    footerFactory = nullptr;
}

VisitorEventListPage::~VisitorEventListPage()
{
//    delete mainLayout;
}
