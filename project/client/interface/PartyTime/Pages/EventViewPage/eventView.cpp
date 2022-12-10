#include "eventView.hpp"

#include <QLabel>
#include <QToolBar>
#include <QBoxLayout>
#include <QAction>
#include <iostream>
#include <QWidget>

EventViewPage::EventViewPage(QWidget *parent) : painter(parent), mainLayout(new QVBoxLayout(this)),
//    form(new painter(this)),
    addButton(new QPushButton()),
    closeFormButton(new QPushButton())
{

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
}

void EventViewPage::onAdd()
{
    form = new painter(this);
    form->setProperty("cssClass", "formEvent");
    form->setGeometry(300, 300, 1000, 600);
    QVBoxLayout* formLayout = new QVBoxLayout(form);

    QLabel* formTitle = new QLabel("New event");
    form->setStyleSheet("color: #000000; font-size: 28px; font-weight: 900");
    formLayout->addWidget(formTitle, 1, Qt::AlignTop | Qt::AlignCenter);
    form->show();
}

void EventViewPage::onRemove()
{
    form->hide();
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
