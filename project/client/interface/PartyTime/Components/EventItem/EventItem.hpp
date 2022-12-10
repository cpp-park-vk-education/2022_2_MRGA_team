#pragma once  // pragma once

#include "Button.hpp"
#include "Label.hpp"

class EventItem : public painter {
    Q_OBJECT

public:
    explicit EventItem(QWidget *parent = nullptr);
    EventItem(const QString& itemType);
    ~EventItem();

    EventItem(const std::initializer_list<QString>& list);

//    EventItem* create(const QString& typeEvent);
    void updateState(const std::initializer_list<QString>& list); // либо человек подписан на событие либо не подписан

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
    QLabel* visitors;
    QLabel* maxVisitors;
    QLabel* address;
    QLabel* time;
    QLabel* date;

    QPushButton* deleteButton;

private slots:
    void onSubcribeClicked();
};
