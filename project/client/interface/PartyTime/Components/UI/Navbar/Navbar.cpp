#include "Navbar.hpp"

Navbar::Navbar(size_t navbarSize, QWidget *parent) : painter(parent), layout(new QHBoxLayout())
{
    if (navbarSize == 3) {

    } else {

    }
}

Navbar::Navbar(const UiButton &_mainBtn, const UiButton &_profileBtn, const UiButton &_eventsBtn, bool _state) : layout(new QHBoxLayout()),
    mainButton(_mainBtn), profileButton(_profileBtn), eventsButton(_eventsBtn), stateNavbar(_state)
{
    layout->addWidget(&mainButton);
    layout->addWidget(&profileButton);
    layout->addWidget(&eventsButton);
}

Navbar::Navbar(const UiButton &_mainBtn, const UiButton &_profileBtn, bool _state) : layout(new QHBoxLayout()),
    mainButton(_mainBtn), profileButton(_profileBtn), stateNavbar(_state)
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
    this->mainButton = other.mainButton;
    this->profileButton = other.profileButton;
    this->eventsButton = other.eventsButton;
    this->layout = other.layout;

    layout->addWidget(&mainButton);
    layout->addWidget(&profileButton);
    layout->addWidget(&eventsButton);

    return *this;
}

Navbar::~Navbar()
{
    delete layout;
}


Navbar* Navbar::create(const QString& objectType) {
    if (objectType == "visitor") {
        return new Navbar(); // navbar visitor тут как раз таки можно вызывать Navbar с size-ом
    }
    return new Navbar(); // navbar orginizator тут как раз таки можно вызывать Navbar с size-ом
}
