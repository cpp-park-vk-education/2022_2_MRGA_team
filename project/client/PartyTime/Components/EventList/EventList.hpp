#pragma once // pragma once

#include "EventItem.hpp"
#include <vector>
#include <map>
#include <iostream>

class EventList : public painter {
    Q_OBJECT


public:
    explicit EventList(QWidget* parrent = nullptr);
    EventList(const QString& evnentListType, size_t size = 0, const QString& styleSheet = "");
    EventList(const EventList& other);
    EventList& operator=(const EventList& other);
    ~EventList();

    void addEvent(const unsigned int _newId, const std::initializer_list<QString>& list);
    void addEvent(EventItem* newEvent);
    void removeEvent(const unsigned int _eventId);
    void clearEventList();

    void minPriceSort() {}
    void minRoadSort() {}

    void updateState(){}; // const std::initializer_list<QString>&

    EventList* create(const QString& objType);
    std::map<unsigned int, EventItem*>* getEventList() {return &eventList;}
    EventItem* getEvent(const unsigned int& _eventId) {return eventList[_eventId];}

private slots:
    // обработчики сигналов с event-ов
    void handleEventSignal(unsigned int eventId);
    void subscribeHandler(unsigned int _eventId) {std::cout << "EVENTLIST Subscribe" << std::endl; emit this->subscribeEvent(_eventId);}
    void leaveEventHandler(unsigned int _eventId) {std::cout << "EVENTLIST Leave" << std::endl; emit this->leaveOnEvent(_eventId);}

signals:
    void openEditForm(unsigned int eventId);
    void subscribeEvent(unsigned int eventId);
    void leaveOnEvent(unsigned int eventId);

private:
    QVBoxLayout* mainLayout;
    QScrollArea* scroll;
    painter* scrollWidget;
    QVBoxLayout scrollLayout;
//    std::vector<EventItem*> eventList;
    std::map<unsigned int, EventItem*> eventList;
    UiButton sortButton;
};
