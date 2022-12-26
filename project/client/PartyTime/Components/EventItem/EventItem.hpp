#pragma once  // pragma once

#include "Button.hpp"
#include "Label.hpp"

class EventItem : public painter {
    Q_OBJECT

public:
    explicit EventItem(QWidget *parent = nullptr);
    EventItem(const QString& itemType, const unsigned int _eventId);
    ~EventItem();

    EventItem(const unsigned int _eventId, const std::initializer_list<QString>& list);
    EventItem(const unsigned int _eventId, const QString& eventType, const std::string& _descr,
                         const std::string& _title,
                         const unsigned int& _visitors,
                         const unsigned int& _maxVisitors,
                         const std::string& _date,
                         const std::string& _time,
                         const std::string& _address
              );

    void updateState(const std::string& _descr,
                     const std::string& _title,
                     const unsigned int& _visitors,
                     const unsigned int& _maxVisitors,
                     const std::string& _date,
                     const std::string& _time,
                     const std::string& _address);

    void updateState(const std::initializer_list<QString>& list); // либо человек подписан на событие либо не подписан

    friend class EventList;
    friend class VisitorEventListPage;
    QPushButton* getSubscribeButton() {return &subscibeButton;}
    void setId(unsigned int newId) {eventId = newId;}
    unsigned int getId() {return eventId;}

    QLabel* getEventName(){return &this->eventTitle;}
    QLabel* getDescription(){return &this->eventDecsription;}
    QLabel* getDate(){return this->date;}
    QLabel* getTime(){return this->time;}
    QLabel* getAddress(){return this->address;}
    QLabel* getMaxVisitors(){return this->maxVisitors;}

private:
    unsigned int eventId;

    QHBoxLayout eventItemLayout;
    QVBoxLayout* leftSide;
    QVBoxLayout* descrptionLayout;
    QHBoxLayout* topContainer;
    QVBoxLayout* informationLayout;
    QVBoxLayout* visitorsInfoLayout;
    QHBoxLayout* dateTimeLayout;

    // TODO: переделать все в UI компоненты
    QPushButton subscibeButton;
    QLabel eventDecsription;
    QLabel userAvatar;
    QLabel eventTitle;
    QLabel* visitors;
    QLabel* maxVisitors;
    QLabel* address;
    QLabel* time;
    QLabel* date;
    QPushButton* deleteButton;
    QDateTimeEdit* dateTime;

private slots:
    void onSubcribeClicked();

signals:
    void callEditForm(unsigned int eventId);
};
