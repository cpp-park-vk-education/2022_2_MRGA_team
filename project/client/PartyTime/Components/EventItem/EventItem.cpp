#include "EventItem.hpp"
#include <iostream>
#include <QAudioOutput>
#include <QVideoWidget>



EventItem::EventItem(QWidget *parent) : painter(parent), eventItemLayout(this),
    leftSide(new QVBoxLayout), informationLayout(new QVBoxLayout),
    visitorsInfoLayout(new QVBoxLayout),
    dateTimeLayout(new QHBoxLayout),
    subscibeButton("Subscribe"),
    eventDecsription("Description"), deleteButton(new QPushButton()),
    dateTime(new QDateTimeEdit())
{
    this->setProperty("cssClass", "eventItem");                                         // TODO: сделать так чтобы background для каждого EventItem был униакальный, а все отслальное одинаковое
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
//    leftSide->addWidget(&subscibeButton, Qt::AlignLeft | Qt::AlignTop);
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

    topContainer = new QHBoxLayout();
    this->eventTitle.setText("Max Korzh сoncert");
    eventTitle.setStyleSheet("color: #ffffff; font-size: 24px; font-weight: 900;");
    topContainer->addWidget(&eventTitle, 20, Qt::AlignTop | Qt::AlignCenter);
    informationLayout->addLayout(topContainer, Qt::AlignTop | Qt::AlignCenter);

    visitorsInfoLayout->setContentsMargins(0, 0, 0, 100);
    visitors = new QLabel("People: ");
//    visitors->setContentsMargins(0, 0, 50, 0);
    visitors->setMaximumWidth(300);
    visitors->setStyleSheet("min-height: 30px; color: #ffffff; font-size: 18px; font-weight: 700;");
    visitorsInfoLayout->addWidget(visitors, 0, Qt::AlignLeft | Qt::AlignTop);
    maxVisitors = new QLabel("Maximum people: ");
    maxVisitors->setMaximumWidth(300);
    maxVisitors->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: 700;");
    visitorsInfoLayout->addWidget(maxVisitors, 1, Qt::AlignLeft | Qt::AlignTop);
    informationLayout->addLayout(visitorsInfoLayout);

    this->deleteButton->setProperty("cssClass", "deleteEventBtn");

    date = new QLabel("28.12.2022");
    date->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: 700;");
    dateTimeLayout->addWidget(date, 0, Qt::AlignLeft | Qt::AlignTop);
    time = new QLabel("22:00");
    time->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: 700;");
    dateTimeLayout->addWidget(time, 1, Qt::AlignLeft | Qt::AlignTop);

    informationLayout->addLayout(dateTimeLayout);

    date->setMaximumWidth(300);
    date->setContentsMargins(0, 0, 100, 0);
    time->setMaximumWidth(50);
    address = new QLabel("Moscow, Arbatskaya street, 30");
    address->setStyleSheet("color: #ffffff; font-size: 18px; font-weight: 700;");
    informationLayout->addWidget(address, 4, Qt::AlignLeft | Qt::AlignBottom);

    eventItemLayout.addLayout(informationLayout);
    eventItemLayout.setAlignment(Qt::AlignLeft);
    eventItemLayout.setSizeConstraint(QLayout::SetDefaultConstraint);

    connect(&this->subscibeButton, &QPushButton::clicked, this, &EventItem::onSubcribeClicked);
}

EventItem::EventItem(const QString &itemType) : EventItem()
{

//    leftSide->addWidget(&subscibeButton, Qt::AlignLeft | Qt::AlignTop);
//    if (itemType != "organizer") {

    std::cout << itemType.toStdString() << std::endl;
    if (itemType != "organizer") {
        leftSide->addWidget(&subscibeButton, Qt::AlignLeft | Qt::AlignTop);
    }

    if (itemType == "organizer") {
        std::cout << "event constructor was called "<< std::endl;
        this->deleteButton->setProperty("cssClass", "deleteEventBtn");
        topContainer->addWidget(deleteButton, 3, Qt::AlignRight | Qt::AlignTop);
    }
}

EventItem::~EventItem()
{
    delete dateTimeLayout;
    delete visitorsInfoLayout;
    delete informationLayout;
    delete leftSide;
}

EventItem::EventItem(const std::initializer_list<QString>& list) : EventItem("organizer")
{
    std::vector<QString> initFieldList(7);
    size_t i = 0;
    for (const auto& elem : list) {
        initFieldList[i] = elem;
        ++i;
    }

    eventDecsription.setText(initFieldList[0]);
    eventTitle.setText(initFieldList[1]);
    visitors->setText(visitors->text() + initFieldList[2]);
    maxVisitors->setText(maxVisitors->text() + initFieldList[3]);
    date->setText(initFieldList[4]);
    time->setText(initFieldList[5]);
    address->setText(initFieldList[6]);
}

EventItem::EventItem(const QString& eventType, const std::string& _descr,
                     const std::string& _title,
                     const unsigned int& _visitors,
                     const unsigned int& _maxVisitors,
                     const std::string& _date,
                     const std::string& _time,
                     const std::string& _address) : EventItem(eventType) {
        eventDecsription.setText(QString::fromStdString(_descr));
        eventTitle.setText(QString::fromStdString(_title));
        visitors->setText(visitors->text() + QString::fromStdString(std::to_string(_visitors)));
        maxVisitors->setText(maxVisitors->text() + QString::fromStdString(std::to_string(_maxVisitors)));
        date->setText(QString::fromStdString(_date));
        time->setText(QString::fromStdString(_time));
        address->setText(QString::fromStdString(_address));
}

void EventItem::updateState(const std::initializer_list<QString> &list)
{
    std::vector<QString> initFieldList(list.size());
    for (const auto& elem : list) {
        initFieldList.push_back(elem);
    }

    eventTitle.setText(initFieldList[0]);
    eventDecsription.setText(initFieldList[1]);
    visitors->setText(visitors->text() + initFieldList[2]);
    maxVisitors->setText(maxVisitors->text() + initFieldList[3]);
    date->setText(date->text() + initFieldList[4]);
    time->setText(time->text() + initFieldList[5]);
    address->setText(initFieldList[6]);
}

void EventItem::parseDateTime()
{
}

void EventItem::onSubcribeClicked()
{
    if (subscibeButton.text() == "Subscribe") {
        subscibeButton.setText("Leave");
    } else {
        subscibeButton.setText("Subscribe");
    }
}
