#include "Navbar.hpp"
#include <iostream>

Navbar::Navbar(const QString& styleSheet, size_t navbarSize, QWidget *parent) : painter(parent), layout(new QHBoxLayout(this))
{
    // создаём UI компоненты для Navbar-a
    UiButton* buttonFactory = new UiButton("", styleSheet);
    // по дефолту все кнопки одинаковые
    mainButton = *buttonFactory;
    profileButton = *buttonFactory;
    eventsButton = *buttonFactory;

//    cтили для кнопок
    mainButton.updateState("mainBtn", "");
    mainButton.button->setText("Main");

    profileButton.updateState("profileBtn", "");
    profileButton.button->setText("Profile");

    eventsButton.updateState("eventsBtn", "");
    eventsButton.button->setText("Events");

    // Выбираем navbar
    if (navbarSize == 3) {
        // Navbar клиента. Закидываем в layout, созданные UI компоненты.
        this->setObjectName("idClientNavbar");        // установили id-ик navbar-у, которым в теории сможем потом воспользоваться
        this->setProperty("cssClass", "clientNavbar");    // установили class navbar-у, который сейчас используется
        std::cout << "afascascsa" << std::endl;
        layout->addWidget(&mainButton);
        layout->addWidget(&profileButton);
        layout->addWidget(&eventsButton);
    } else {
        this->setObjectName("idOrganizerNavbar");        // установили id-ик navbar-у, которым в теории сможем потом воспользоваться
        this->setProperty("cssClass", "organizerNavbar");    // установили class navbar-у, который сейчас используется

        layout->addWidget(&mainButton);
        layout->addWidget(&profileButton);
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
    this->profileButton = other.profileButton;
    this->eventsButton = other.eventsButton;
    this->layout = other.layout;

    layout->addWidget(&mainButton);
    layout->addWidget(&profileButton);
    layout->addWidget(&eventsButton);
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
    this->profileButton = other.profileButton;
    this->eventsButton = other.eventsButton;

    this->layout->addWidget(&mainButton);
    this->layout->addWidget(&profileButton);
    this->layout->addWidget(&eventsButton);

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
