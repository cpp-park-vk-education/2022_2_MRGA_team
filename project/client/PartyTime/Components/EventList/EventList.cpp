#include "EventList.hpp"


EventList::EventList(QWidget* parent) : painter(parent), 
    mainLayout(new QVBoxLayout(this)),
    scroll(new QScrollArea()),
    scrollWidget(new painter()),
    scrollLayout(),
    eventList(std::vector<EventItem*>())
{
    this->setProperty("cssClass", "eventList");
    scrollWidget->setStyleSheet("border-radius: 15px;");
    scrollWidget->setLayout(&scrollLayout);
    scroll->setWidget(scrollWidget);
    scroll->setWidgetResizable(true);
    mainLayout->addWidget(scroll);
}


EventList::EventList(const QString &evnentListType, size_t size, const QString &styleSheet) : mainLayout(new QVBoxLayout(this)),
    scroll(new QScrollArea()),
    scrollWidget(new painter()),
    scrollLayout(),
    eventList(std::vector<EventItem*>())
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
        EventItem* event = new EventItem(evnentListType);
        eventList.push_back(event);
        scrollLayout.addWidget(event);
    }
}


EventList::EventList(const EventList &other) : painter(new QWidget)
{
    this->eventList.clear();
    for (auto& elem : other.eventList) {
        this->eventList.push_back(elem);
        scrollLayout.addWidget(elem);
    }
}

EventList &EventList::operator=(const EventList &other)
{
    this->eventList.clear();
    for (auto& elem : other.eventList) {
        this->eventList.push_back(elem);
        scrollLayout.addWidget(elem);
    }
    return *this;
}

EventList::~EventList()
{

}

void EventList::addEvent(const std::initializer_list<QString>& list)
{
    EventItem* newEvent = new EventItem(list); // ("organizer", list
    this->eventList.push_back(newEvent);
    scrollLayout.addWidget(newEvent);
}

void EventList::addEvent(EventItem* newEvent)
{
    this->eventList.push_back(newEvent);
    scrollLayout.addWidget(newEvent);
}

void EventList::removeEvent()
{

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
