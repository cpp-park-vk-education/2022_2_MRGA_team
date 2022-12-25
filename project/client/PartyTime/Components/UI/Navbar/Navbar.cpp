#include "Navbar.hpp"
#include <iostream>
#include <QSvgWidget>

Navbar::Navbar(const QString& styleSheet, size_t navbarSize, QWidget *parent) : painter(parent), layout(new QHBoxLayout(this))
{
//    layout->setAlignment(Qt::AlignTop);
    // создаём UI компоненты для Navbar-a
    UiButton* buttonFactory = new UiButton("", styleSheet);
    // по дефолту все кнопки одинаковые
    mainButton = *buttonFactory;
    profileButton = *buttonFactory;
    eventsButton = *buttonFactory;
    // settingsButton = *buttonFactory;

//    cтили для кнопок
//    mainButton.updateState("mainBtn", "");
    mainButton.updateState("mainBtn", "");
    mainButton.button->setText("Main");

//    profileButton.updateState("profileBtn", "");
    profileButton.updateState("profileBtn", "");
    profileButton.button->setText("Profile");

    eventsButton.updateState("eventsBtn", "");
    eventsButton.button->setText("Events");

     logoutButton.updateState("profileBtn", "");
     logoutButton.getButton()->setStyleSheet("background-color: none;");
     logoutButton.button->setText("Logout");

    // Выбираем navbar
    if (navbarSize == 3) {
        // Navbar клиента. Закидываем в layout, созданные UI компоненты.
        this->setProperty("cssClass", "clientNavbar");    // установили class navbar-у, который сейчас используется
        layout->addWidget(&mainButton);
        layout->addWidget(&eventsButton);
        layout->addWidget(&logoutButton);
//        layout->addWidget(&profileButton);
//        layout->addWidget(svgButton);
    } else {
        this->setProperty("cssClass", "organizerNavbar");    // установили class navbar-у, который сейчас используется
        layout->addWidget(&mainButton);
        layout->addWidget(&logoutButton);
//        layout->addWidget(&profileButton);
//        layout->addWidget(svgButton);
    }
    delete buttonFactory;
}

Navbar::Navbar(const QString& mainBtnType, const QString& profileBtnType, const QString& eventsBtnType)
{
    if (mainBtnType == "" && profileBtnType == "" && eventsBtnType == "") {} // заглушка
}

Navbar::Navbar(const UiButton &_mainBtn, const UiButton &_profileBtn, const UiButton &_eventsBtn) : layout(new QHBoxLayout()),
    mainButton(_mainBtn), profileButton(_profileBtn), eventsButton(_eventsBtn)
{

}

Navbar::Navbar(const UiButton &_mainBtn, const UiButton &_profileBtn) : layout(new QHBoxLayout()),
    mainButton(_mainBtn), profileButton(_profileBtn)
{
    layout->addWidget(&mainButton);
    layout->addWidget(&profileButton);
}

Navbar::Navbar(const Navbar &other): painter(new QWidget)
{
    this->mainButton = other.mainButton;
    this->eventsButton = other.eventsButton;
//    this->profileButton = other.profileButton;
    this->logoutButton = other.logoutButton;
//    this->layout = other.layout;

    layout->addWidget(&mainButton);
    layout->addWidget(&eventsButton);
//    layout->addWidget(&profileButton);
    layout->addWidget(&logoutButton);
}

Navbar &Navbar::operator=(const Navbar &other)
{
    if (other.objectName() == "idClientNavbar") {
        this->setProperty("cssClass", "clientNavbar");
    }

    if (other.objectName() == "idOrganizerNavbar") {
        this->setProperty("cssClass", "organizerNavbar");
    }

    this->mainButton = other.mainButton;
    this->eventsButton = other.eventsButton;
//    this->profileButton = other.profileButton;
     this->logoutButton = other.logoutButton;

    this->layout->addWidget(&mainButton);
    this->layout->addWidget(&eventsButton);
    // this->layout->addWidget(&settingsButton);
    // this->layout->addWidget(&profileButton);
    this->layout->addWidget(&logoutButton);
    return *this;
}

Navbar::~Navbar()
{
    delete layout;
}


Navbar* Navbar::create(const QString& objectType) {
    if (objectType == "visitor") {
        return new Navbar("", 3); // navbar visitor тут как раз таки можно вызывать Navbar с size-ом
    }
    if (objectType == "organizer") {
        return new Navbar("", 2); // navbar visitor тут как раз таки можно вызывать Navbar с size-ом
    }
    return new Navbar("background-color: red"); // navbar orginizator тут как раз таки можно вызывать Navbar с size-ом
}
