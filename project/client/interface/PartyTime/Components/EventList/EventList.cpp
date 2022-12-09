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
    scrollWidget->setObjectName("scrollBackground");
    scrollWidget->setLayout(&scrollLayout);
    scroll->setWidget(scrollWidget);
    scroll->setWidgetResizable(true);

    mainLayout->addWidget(scroll);

    for (int i = 0; i < 10; ++i) {
        EventItem* event = new EventItem();
        eventList.push_back(event);
        scrollLayout.addWidget(event);
    }
}

EventList::EventList(const QString &evnentListType, size_t size, const QString &styleSheet)
{
    if (evnentListType == "" && size != 0 && styleSheet == "") {

    }
}

EventList::EventList(const EventList &other) : painter(new QWidget)
{
    this->mainLayout = other.mainLayout;
//    this->scroll = other.scroll;
//    this->scrollWidget = other.scrollWidget;
//    this->scrollLayout = other.scrollLayout;
//    this->sortButton = other.sortButton;
}

EventList &EventList::operator=(const EventList &other)
{
    this->mainLayout = other.mainLayout;
//    this->scroll = other.scroll;
//    this->scrollWidget = other.scrollWidget;
//    this->scrollLayout = other.scrollLayout;
//    this->sortButton = other.sortButton;
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
