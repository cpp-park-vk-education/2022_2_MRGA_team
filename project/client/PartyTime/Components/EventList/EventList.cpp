#include "EventList.hpp"
#include <iostream>

EventList::EventList(QWidget* parent) : painter(parent), 
    mainLayout(new QVBoxLayout(this)),
    scroll(new QScrollArea()),
    scrollWidget(new painter()),
    scrollLayout(),
    eventList(std::map<unsigned int, EventItem*>())
{
    this->setProperty("cssClass", "eventList");
    scrollWidget->setStyleSheet("border-radius: 15px; background-color: #ffffff");
    scrollWidget->setLayout(&scrollLayout);
    scroll->setWidget(scrollWidget);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("border-radius: 15px; background-color: #ffffff");
    mainLayout->addWidget(scroll);

    for (const auto& event : this->eventList) {
        connect(this->eventList[event.first], &EventItem::callEditForm, this, &EventList::handleEventSignal);
        connect(this->eventList[event.first], &EventItem::subscibeOnEvent, this, &EventList::subscribeHandler);
        connect(this->eventList[event.first], &EventItem::leaveOnEvent, this, &EventList::leaveEventHandler);
    }
}


EventList::EventList(const QString &evnentListType, size_t size, const QString &styleSheet) : mainLayout(new QVBoxLayout(this)),
    scroll(new QScrollArea()),
    scrollWidget(new painter()),
    scrollLayout(),
    eventList(std::map<unsigned int, EventItem*>())
{
    this->setProperty("cssClass", "eventList");
    scrollWidget->setStyleSheet("border-radius: 15px;");
    scrollWidget->setLayout(&scrollLayout);
    scroll->setWidget(scrollWidget);
    scroll->setWidgetResizable(true);

    if (styleSheet != "") {
        this->setStyleSheet(styleSheet);
    }

    mainLayout->addWidget(scroll);

    for (size_t i = 0; i < size; ++i) {
        EventItem* event = new EventItem(evnentListType, i);
        eventList[i] = event;
        scrollLayout.addWidget(event);
    }

    for (const auto& event : this->eventList) {
        connect(this->eventList[event.first], &EventItem::callEditForm, this, &EventList::handleEventSignal);
        connect(this->eventList[event.first], &EventItem::subscibeOnEvent, this, &EventList::subscribeHandler);
        connect(this->eventList[event.first], &EventItem::leaveOnEvent, this, &EventList::leaveEventHandler);
    }
}


EventList::EventList(const EventList &other) : painter(new QWidget)
{
    this->eventList.clear();
    for (auto& elem : other.eventList) {
        this->eventList[elem.first] = elem.second;
        scrollLayout.addWidget(elem.second);
    }

    for (const auto& event : this->eventList) {
        connect(this->eventList[event.first], &EventItem::callEditForm, this, &EventList::handleEventSignal);
        connect(this->eventList[event.first], &EventItem::subscibeOnEvent, this, &EventList::subscribeHandler);
        connect(this->eventList[event.first], &EventItem::leaveOnEvent, this, &EventList::leaveEventHandler);
    }
}

EventList &EventList::operator=(const EventList &other)
{
    this->eventList.clear();

    for (auto& elem : other.eventList) {
        this->eventList[elem.first] = elem.second;
        scrollLayout.addWidget(elem.second);
    }

    for (const auto& event : this->eventList) {
        connect(this->eventList[event.first], &EventItem::callEditForm, this, &EventList::handleEventSignal);
        connect(this->eventList[event.first], &EventItem::subscibeOnEvent, this, &EventList::subscribeHandler);
        connect(this->eventList[event.first], &EventItem::leaveOnEvent, this, &EventList::leaveEventHandler);
    }

    return *this;
}

EventList::~EventList()
{

}

void EventList::addEvent(const unsigned int _newId, const std::initializer_list<QString>& list)
{
    EventItem* newEvent = new EventItem(_newId, list);
    this->eventList.insert(std::make_pair(newEvent->getId(), newEvent));
    connect(this->eventList[newEvent->getId()], &EventItem::callEditForm, this, &EventList::handleEventSignal);
    connect(this->eventList[newEvent->getId()], &EventItem::subscibeOnEvent, this, &EventList::subscribeHandler);
    connect(this->eventList[newEvent->getId()], &EventItem::leaveOnEvent, this, &EventList::leaveEventHandler);
    scrollLayout.addWidget(newEvent);
}

void EventList::addEvent(EventItem* newEvent)
{
    this->eventList[newEvent->getId()] = newEvent;
    connect(this->eventList[newEvent->getId()], &EventItem::callEditForm, this, &EventList::handleEventSignal);
    connect(this->eventList[newEvent->getId()], &EventItem::subscibeOnEvent, this, &EventList::subscribeHandler);
    connect(this->eventList[newEvent->getId()], &EventItem::leaveOnEvent, this, &EventList::leaveEventHandler);
    scrollLayout.addWidget(newEvent);
}

void EventList::removeEvent(const unsigned int _eventId)
{
    auto key = this->eventList.find(_eventId);
    if (key != this->eventList.end()) {
        this->eventList.erase(key);
        QLayoutItem* item = scrollLayout.takeAt(_eventId);
        delete item->widget();
        delete item;
    }
}

void EventList::clearEventList()
{
    eventList.clear();
    while (QLayoutItem* item = scrollLayout.takeAt(0)) {
        delete item->widget();
        delete item;
    }
}

EventList *EventList::create(const QString &objType)
{
    if (objType == "") {
        return new EventList();
    }
    return new EventList();
}

void EventList::handleEventSignal(unsigned int eventId)
{
    emit openEditForm(eventId);
}
