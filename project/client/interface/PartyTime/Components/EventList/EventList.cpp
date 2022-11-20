#include "EventList.hpp"

EventList::EventList(QWidget* parent) : painter(parent)
{

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
