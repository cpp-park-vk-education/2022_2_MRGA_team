#pragma once  // pragma once

#include "Button.hpp"
#include "Label.hpp"

class EventItem : public painter {
    Q_OBJECT

public:
    explicit EventItem(QWidget* parent = nullptr);
    EventItem(const QString& _userPhoto, const std::initializer_list<QString>& list);
//    EventItem(const EventItem& other);
//    EventItem& operator=(const EventItem& other);
    ~EventItem();

//    void setDescription(const QString& _descr);
//    void setData(const QString& _data);
//    void setTime(const QString& _time);
//    void setPeopleNumber(const QString& _number);
//    void setEventTime(const QString& _time);
//    void setAddress(const QString& _address);
//    void setCheck(const QString& _check);
//    void setMaxPeople(const QString& _maxCount);

    EventItem* create(const QString& typeEvent);
private:
    QGridLayout* mainLayout;
    QVBoxLayout* leftSide;
    QVBoxLayout* rightSide;
    QVBoxLayout* rigthTop;
    QHBoxLayout* rightBottom;

    UiLabel userAvatar;
    UiButton subScribe;
    std::map<QString, QString> fieldsMap;

//    UiLabel description;
//    UiLabel data;
//    UiLabel time;
//    UiLabel peopleNumber;

//    UiLabel eventTime;
//    UiLabel address;
//    UiLabel averageCheck;
//    UiLabel maxPeopleCount;
};
