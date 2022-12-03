#include "Label.hpp"

UiLabel::UiLabel(QWidget *parent) : painter(parent), label(new QLabel("Тыкни на меня")), labelLayout(new QHBoxLayout(this))
{
    labelLayout->addWidget(label);
}

UiLabel::UiLabel(const UiLabel &other): painter(new QWidget)
{
    label = other.label;
    labelLayout->addWidget(label);
    labelLayout = other.labelLayout;
}

UiLabel &UiLabel::operator=(const UiLabel &other)
{
    this->label = other.label;
    this->labelLayout = other.labelLayout;
    return *this;
}

UiLabel::~UiLabel()
{
    delete label;
    delete labelLayout;
}

UiLabel::UiLabel(const QString &styleSheet, const QPixmap &labelImage, int width, int height, int coordX, int coordY)
{
    label->setStyleSheet(styleSheet);
    label->setPixmap(labelImage);
    label->setGeometry(coordX, coordY, width, height);
    labelLayout->addWidget(label);
}

UiLabel::UiLabel(const QString &styleSheet, const QFont &font, int width, int height, int coordX, int coordY)
{
    label->setStyleSheet(styleSheet);
    label->setFont(font);
    label->setGeometry(coordX, coordY, width, height);
    labelLayout->addWidget(label);
}

UiLabel::UiLabel(const QString &styleSheet, QMovie *movie)
{
    label->setStyleSheet(styleSheet);
    label->setMovie(movie);
    labelLayout->addWidget(label);
}

UiLabel *UiLabel::create(const QString &objectType)
{
    if (objectType == "regLabel") {
        return new UiLabel("padding: 10px");
    }
    return new UiLabel();
}
