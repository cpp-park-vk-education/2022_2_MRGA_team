#include "EventList.hpp"

EventList::EventList(QWidget* parent) : painter(parent)
{

}

EventList::EventList(const QString &evnentListType, size_t size, const QString &styleSheet)
{
    if (evnentListType == "" && size != 0 && styleSheet == "") {

    }
}

EventList::EventList(const EventList &other) : painter(new QWidget)
{
    this->mainLayout = other.mainLayout;
    this->scroll = other.scroll;
    this->scrollWidget = other.scrollWidget;
    this->scrollLayout = other.scrollLayout;
    this->sortButton = other.sortButton;
}

EventList &EventList::operator=(const EventList &other)
{
    this->mainLayout = other.mainLayout;
    this->scroll = other.scroll;
    this->scrollWidget = other.scrollWidget;
    this->scrollLayout = other.scrollLayout;
    this->sortButton = other.sortButton;
    return *this;
}

EventList::~EventList()
{

}

EventList *EventList::create(const QString &objType)
{
    if (objType == "") {
        return new EventList();
    }
    return new EventList();
}
