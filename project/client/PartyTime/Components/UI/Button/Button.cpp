#include "Button.hpp"
#include <iostream>
#include <QSvgWidget>

UiButton::UiButton(QWidget *parent): painter(parent), button(new QPushButton("Тыкни на меня")), btnLayout(new QHBoxLayout(this))
{
    button->setStyleSheet("background-color: rgba(47, 5, 72, 1);");
    btnLayout->addWidget(button);
}

UiButton::UiButton(const QString& id, const QString &styleSheet, const QString &btnText, const QFont &font) : button(new QPushButton("Клацни на меня")), btnLayout(new QHBoxLayout(this))
{
    if (!id.isEmpty()) {
        this->setObjectName(id);
    }

    if (!styleSheet.isEmpty()) {
        this->setStyleSheet(styleSheet);
    }

    if (btnText != "") {
        button->setText(btnText);
    }

    if (font != QFont()) {
        button->setFont(font);
    }

    btnLayout->addWidget(button);
}

UiButton* UiButton::create(const QString &objectType)
{
    if (objectType == "navbarButton") {
        return new UiButton(objectType, "background-color: rgba(47, 5, 72, 1); color: black; min-width: 100px; min-height: 10px; border-radius: 10px;");
    }

    if (objectType == "regButton") {
        return new UiButton(objectType, "padding: 10px");
    }

    return new UiButton(); // создаться default-ая кнопка
}

void UiButton::updateState(const QString &newId, const QString& newStyle, const QString& newText)
{
    if (!newId.isEmpty()) {
        this->button->setObjectName(newId);
    }
    if (!newStyle.isEmpty()) {
        this->button->setStyleSheet(newStyle);
    }
    if  (!newText.isEmpty()) {
        this->button->setText(newText);
    }
}

UiButton::UiButton(const UiButton &other): painter(new QWidget)
{
    this->button->setText(other.button->text());
    this->button->setStyleSheet(other.button->styleSheet());
}

UiButton &UiButton::operator=(const UiButton &other)
{
    this->button->setText(other.button->text());
    this->button->setStyleSheet(other.button->styleSheet());
    return *this;
}

UiButton::~UiButton()
{
    delete button;
    button = nullptr;
}

UiButton::UiButton(const QString& path, const QSize &size) : btnLayout(new QHBoxLayout(this))
{
    QVBoxLayout *mainContainer = new QVBoxLayout;
    QSvgWidget *image = new QSvgWidget(path);
    image->setMaximumSize(size);
    image->setMinimumSize(size);
    mainContainer->addWidget(image);
    mainContainer->setContentsMargins(0,0,0,0);
    image->setStyleSheet("background-color:#FFFFFF;");
    this->setStyleSheet("border:none;padding:0px; background-color:#FFFFFF;");
    this->setMinimumSize(size);
    this->setMaximumSize(size);
    this->setLayout(mainContainer);
}


UiButton::UiButton(const QString &styleSheet, int width, int height, int coordX, int coordY) : button(new QPushButton("What ?")), btnLayout(new QHBoxLayout(this))
{
    button->setGeometry(coordX, coordY, width, height);
    button->setStyleSheet(styleSheet);
    btnLayout->addWidget(button);
}

UiButton::UiButton(const QString &styleSheet, const QString &text, const QIcon &backgroundImage, size_t width, size_t height) : button(new QPushButton("AAAA")), btnLayout(new QHBoxLayout(this))
{
    button->setStyleSheet(styleSheet);
    button->setText(text);
    button->setIcon(backgroundImage);
    button->setBaseSize(width, height);
    btnLayout->addWidget(button);
}
