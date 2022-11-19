#include "Button.hpp"


UiButton::UiButton(QWidget *parent): painter(parent), button(new QPushButton("Тыкни на меня")), btnLayout(new QHBoxLayout(this))
{
    btnLayout->addWidget(button);
}

UiButton::UiButton(const UiButton &other): painter(new QWidget)
{
    button = other.button;
    btnLayout->addWidget(button);
    btnLayout = other.btnLayout;
}

UiButton &UiButton::operator=(const UiButton &other)
{
    this->button = other.button;
    return *this;
}

UiButton::~UiButton()
{
    delete button;
    button = nullptr;
}

UiButton::UiButton(const QString &styleSheet, const QString &btnText, const QFont &font) : button(new QPushButton()), btnLayout(new QHBoxLayout(this))
{
    button->setStyleSheet(styleSheet);
    button->setText(btnText);
    button->setFont(font);
    btnLayout->addWidget(button);
}

UiButton::UiButton(const QString &styleSheet, int width, int height, int coordX, int coordY) : button(new QPushButton()), btnLayout(new QHBoxLayout(this))
{
    button->setGeometry(coordX, coordY, width, height);
    button->setStyleSheet(styleSheet);
    btnLayout->addWidget(button);
}

UiButton::UiButton(const QString &styleSheet, const QString &text, const QIcon &backgroundImage, size_t width, size_t height) : button(new QPushButton()), btnLayout(new QHBoxLayout(this))
{
    button->setStyleSheet(styleSheet);
    button->setText(text);
    button->setIcon(backgroundImage);
    button->setBaseSize(width, height);
    btnLayout->addWidget(button);
}

UiButton *UiButton::create(const QString &objectType)
{
    if (objectType == "regButton") {
        return new UiButton("padding: 10px");
    }
    return new UiButton();
}
