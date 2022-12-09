#include "EventItem.hpp"
#include <iostream>
#include <QAudioOutput>
#include <QVideoWidget>



EventItem::EventItem(QWidget *parent) : painter(parent), eventItemLayout(this),
    leftSide(new QVBoxLayout), informationLayout(new QVBoxLayout),
    visitorsInfoLayout(new QVBoxLayout), dateTimeLayout(new QHBoxLayout),
    subscibeButton("Subscribe"),
    eventDecsription("Description")
{
    // TODO: сделать отдельный конструктор Input под поля ниже
    this->setProperty("cssClass", "eventItem"); // TODO: сделать так чтобы background для каждого EventItem был униакальный, а все отслальное одинаковое
    this->setStyleSheet("border-radius: 15px;");

    subscibeButton.setProperty("cssClass", "subscribeButton");

    QPixmap userPhoto(":/image/Ava.jpeg");
    QBitmap map(200, 200);
    map.fill(Qt::color0);
    QPainter painter(&map);
    painter.setBrush(Qt::color1);
    painter.drawRoundedRect(0, 0, 200, 200, 50, 50);
    QPixmap scaled = userPhoto.scaled(200, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scaled.setMask(map);

    userAvatar.setStyleSheet("padding-left: 0px; padding-top: 0px; padding-bottom: 0px;");
    userAvatar.setPixmap(scaled);
    userAvatar.setMaximumWidth(200);
    leftSide->addWidget(&userAvatar, Qt::AlignCenter | Qt::AlignTop);
    leftSide->addWidget(&subscibeButton, Qt::AlignLeft | Qt::AlignTop);
    eventItemLayout.addLayout(leftSide, Qt::AlignLeft | Qt::AlignTop);
    subscibeButton.setMaximumWidth(100);

    QString textDescription = "Мероприятие клубного формата. Начало мероприятия: 23:00. Артист выходит на сцену не ранее 2:00 и является не единственным элементом ночной программы.";
    QString templateString = "<p style=\"line-height:%1%\">%2<p>";
    int myPercentage = 200;
    QString targetText = templateString.arg(myPercentage).arg(textDescription);
    eventDecsription.setText(targetText);
    eventDecsription.setObjectName("eventDescription");
    eventItemLayout.addWidget(&eventDecsription, Qt::AlignLeft);
    eventDecsription.setMaximumWidth(450);
    eventDecsription.setWordWrap(true);

    QLabel* curVisitors = new QLabel("People: 28");
    curVisitors->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: 700;");
    visitorsInfoLayout->addWidget(curVisitors, 0, Qt::AlignLeft | Qt::AlignTop);
    QLabel* maxVisitors = new QLabel("Maximum people: 50");
    maxVisitors->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: 700;");
    visitorsInfoLayout->addWidget(maxVisitors, 1, Qt::AlignLeft | Qt::AlignTop);

    QLabel* date = new QLabel("28.12.2022");
    date->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: 700;");
    dateTimeLayout->addWidget(date, 0, Qt::AlignLeft | Qt::AlignTop);
    QLabel* time = new QLabel("22:00");
    time->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: 700;");
    dateTimeLayout->addWidget(time, 1, Qt::AlignLeft | Qt::AlignTop);

    this->eventTitle.setText("Max Korzh сoncert");
    eventTitle.setStyleSheet("color: #ffffff; font-size: 24px; font-weight: 900;");
    informationLayout->addWidget(&eventTitle, 0, Qt::AlignTop | Qt::AlignCenter);
    informationLayout->addLayout(visitorsInfoLayout, 1);
    visitorsInfoLayout->setContentsMargins(0, 0, 0, 220);

//    QMediaPlayer player;
//    QAudioOutput audio;
//    QVideoFrame video;
//    player.setAudioOutput(&audio);
//    player.setVideoOutput(video);
//    player.setSource("");
//    player.play();

    informationLayout->addLayout(dateTimeLayout, 2);
    date->setMaximumWidth(300);
    date->setContentsMargins(0, 0, 100, 0);
    time->setMaximumWidth(50);
    QLabel* address = new QLabel("Moscow, Arbatskaya street, 30");
    address->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: 700;");
    informationLayout->addWidget(address, 4, Qt::AlignLeft | Qt::AlignBottom);

    eventItemLayout.addLayout(informationLayout);
    eventItemLayout.setAlignment(Qt::AlignLeft);
    eventItemLayout.setSizeConstraint(QLayout::SetDefaultConstraint);

    connect(&this->subscibeButton, &QPushButton::clicked, this, &EventItem::onSubcribeClicked);
}

EventItem::~EventItem()
{
    delete dateTimeLayout;
    delete visitorsInfoLayout;
    delete informationLayout;
    delete leftSide;
}

void EventItem::onSubcribeClicked()
{
    if (subscibeButton.text() == "Subscribe") {
        subscibeButton.setText("Leave");
    } else {
        subscibeButton.setText("Subscribe");
    }
}
