#pragma once // pragma once

#include "EventItem.hpp"

class EventList : public painter {
    Q_OBJECT


public:
    explicit EventList(QWidget* parrent = nullptr);
    EventList(const QString& evnentListType, size_t size = 0, const QString& styleSheet = "");
    ~EventList();

    void minPriceSort();
    void maxPriceSort();

private:

};
