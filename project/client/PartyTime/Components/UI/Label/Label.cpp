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

UiLabel::UiLabel(const QString &styleSheet, const QString &pathToImage, const QString &imageType) : label(new QLabel()), labelLayout(new QHBoxLayout(this))
{
    label->setStyleSheet(styleSheet);
    if (imageType == "userAvatar") {
        QPixmap userPhoto(pathToImage);
        QBitmap map(100, 100);
        map.fill(Qt::color0);
        QPainter painter(&map);
        painter.setBrush(Qt::color1);
        painter.drawRoundedRect(0, 0, 100, 100, 25, 25);
        QPixmap scaled = userPhoto.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaled.setMask(map);
        label->setPixmap(scaled);
    }
    labelLayout->addWidget(label, 1, Qt::AlignLeft);
}

UiLabel::UiLabel(const QString &styleSheet, const QString &text) : label(new QLabel(text)), labelLayout(new QHBoxLayout(this))
{
    label->setStyleSheet(styleSheet);
    labelLayout->addWidget(label);
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
    if (objectType == "text") {
        return new UiLabel("", QFont());
    }
    if (objectType == "image") {
        return new UiLabel("", QPixmap());
    }
    return new UiLabel();
}
