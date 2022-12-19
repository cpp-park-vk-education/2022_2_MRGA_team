#include <iostream>
#include "structs.hpp"

int main() {
    std::error_code ec;
    Event yyevent = Event::fromJSON("fd", ec);
    if (ec) {
        std::cout << ec.message() << std::endl;
    } else {
        std::cout << yyevent.toJSON() << std::endl;
    }
    yyevent = Event::fromJSON(R"json({"title":"Hello World","dateTime":"2022-12-12 12:01:11","userId":0,"address":{"address":"Moscow","longitude":0,"latitude":0},"description":"","currVisitors":0,"id":0})json", ec);
    if (ec) {
        std::cout << ec.message() << std::endl;
    } else {
        std::cout << yyevent.toJSON() << std::endl;
    }
    Event empty_event;
    auto event_json = empty_event.toJSON(ec);
    if (ec) {
        std::cout << ec.message() << std::endl;
    } else {
        std::cout << event_json << std::endl;
    }
    empty_event.title = "NOT empty title";
    event_json = empty_event.toJSON(ec);
    if (ec) {
        std::cout << ec.message() << std::endl;
    } else {
        std::cout << event_json << std::endl;
    }
    empty_event.date_time = "2022-12-12";
    event_json = empty_event.toJSON(ec);
    if (ec) {
        std::cout << ec.message() << std::endl;
    } else {
        std::cout << event_json << std::endl;
    }
    Events events;
    events.events.push_back(yyevent);
    events.events.push_back(yyevent);
    events.events.push_back(yyevent);
    events.events.push_back(yyevent);
    std::cout << events.toJSON() << std::endl;

    return 0;
}