#include "Header.hpp"


Header::Header(QWidget *parent) : painter(parent), layout(new QHBoxLayout())
{
    layout->addWidget(&userAvatar);
    layout->addWidget(&appLogo);
    layout->addWidget(&stateButton);
}

Header::Header(const QString& userAvatarType, const QString& appLogoType, const QString& stateButtonType) : layout(new QHBoxLayout())
{
    if (userAvatarType == "default" && appLogoType != "default" && stateButtonType == "default") {
        
    }
}

Header::Header(const UiLabel &_userAvatar, const UiLabel &_appLogo, const UiButton &_stateButton) : layout(new QHBoxLayout()),
    userAvatar(std::move(_userAvatar)), appLogo(std::move(_appLogo)), stateButton(std::move(_stateButton))
{
}

Header::Header(const Header &other) : painter(new QWidget)
{
    this->userAvatar = other.userAvatar;
    this->appLogo = other.appLogo;
    this->stateButton = other.stateButton;
    this->layout = other.layout;
    layout->addWidget(&userAvatar);
    layout->addWidget(&appLogo);
    layout->addWidget(&stateButton);
}
Header &Header::operator=(const Header &other)
{
    this->userAvatar = other.userAvatar;
    this->appLogo = other.appLogo;
    this->stateButton = other.stateButton;
    this->layout = other.layout;
    layout->addWidget(&userAvatar);
    layout->addWidget(&appLogo);
    layout->addWidget(&stateButton);
    return *this;
}

Header::~Header()
{
    delete layout;
}

Header *Header::create(const QString &objectType)
{
    if (objectType == "otherHeader") {
        return new Header();
    }
    return new Header();
}
