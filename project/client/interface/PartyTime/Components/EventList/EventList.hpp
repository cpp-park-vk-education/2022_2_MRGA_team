#pragma once // pragma once

#include "EventItem.hpp"

class EventList : public painter {
    Q_OBJECT


public:
    explicit EventList(QWidget* parrent = nullptr);
    EventList(const QString& evnentListType, size_t size = 0, const QString& styleSheet = "");
    EventList(const EventList& other);
    EventList& operator=(const EventList& other);
    ~EventList();

    void addEvent() {}
    void removeEvent() {}

    void minPriceSort() {}
    void minRoadSort() {}

    void updateState(){}; // const std::initializer_list<QString>&

    EventList* create(const QString& objType);

private:
    QVBoxLayout* mainLayout;
    QScrollArea* scroll;
    painter* scrollWidget;
    QVBoxLayout* scrollLayout;
    UiButton sortButton;
//    QComboBox filters;
};
