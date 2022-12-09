#pragma once  // pragma once

#include "Button.hpp"
#include "Label.hpp"

class EventItem : public painter {
    Q_OBJECT

public:
    explicit EventItem(QWidget *parent = nullptr);
    ~EventItem();

//    EventItem* create(const QString& typeEvent);
    void updateState(){}; // либо человек подписан на событие либо не подписан

    friend class EventList;
    friend class VisitorEventListPage;
private:
    QHBoxLayout eventItemLayout;
    QVBoxLayout* leftSide;
    QVBoxLayout* informationLayout;
    QVBoxLayout* visitorsInfoLayout;
    QHBoxLayout* dateTimeLayout;
    // TODO: переделать все в UI компоненты
    QPushButton subscibeButton;
    QLabel eventDecsription;
    QLabel userAvatar;
    QLabel eventTitle;

private slots:
    void onSubcribeClicked();
};
