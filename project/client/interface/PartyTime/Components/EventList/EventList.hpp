#pragma once // pragma once

#include "painter.hpp"
#include "Button.hpp"

class EventList : public painter {
    Q_OBJECT


public:
    explicit EventList(QWidget* parrent = nullptr);
    ~EventList();
};
