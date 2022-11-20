#pragma once  // pragma once

#include "Button.hpp"
#include "Label.hpp"

class EventItem : public painter {
    Q_OBJECT

public:
    explicit EventItem(QWidget* parent = nullptr);
    EventItem(const QString& _userPhoto, const std::initializer_list<QString>& list); // буду из структур делать строки
    ~EventItem();

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
};
