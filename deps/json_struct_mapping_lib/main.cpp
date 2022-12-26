#include <iostream>
#include "structs.hpp"

int main() {
    // std::error_code ec;
    // Event yyevent = Event::fromJSON("fd", ec);
    // if (ec) {
    //     std::cout << ec.message() << std::endl;
    // } else {
    //     std::cout << yyevent.toJSON() << std::endl;
    // }
    // yyevent = Event::fromJSON(R"json({"title":"Hello World","dateTime":"2022-12-12 12:01:11","userId":0,"address":{"address":"Moscow","longitude":0,"latitude":0},"description":"","currVisitors":0,"id":0})json", ec);
    // if (ec) {
    //     std::cout << ec.message() << std::endl;
    // } else {
    //     std::cout << yyevent.toJSON() << std::endl;
    // }
    // Event empty_event;
    // auto event_json = empty_event.toJSON(ec);
    // if (ec) {
    //     std::cout << ec.message() << std::endl;
    // } else {
    //     std::cout << event_json << std::endl;
    // }
    // empty_event.title = "NOT empty title";
    // event_json = empty_event.toJSON(ec);
    // if (ec) {
    //     std::cout << ec.message() << std::endl;
    // } else {
    //     std::cout << event_json << std::endl;
    // }
    // empty_event.date_time = "2022-12-12";
    // event_json = empty_event.toJSON(ec);
    // if (ec) {
    //     std::cout << ec.message() << std::endl;
    // } else {
    //     std::cout << event_json << std::endl;
    // }
    // Events events;
    // events.events.push_back(yyevent);
    // events.events.push_back(yyevent);
    // events.events.push_back(yyevent);
    // events.events.push_back(yyevent);
    // std::cout << events.toJSON() << std::endl;
    std::error_code errc;
    // const Event test_event = []{
    //     Event test_event;
    //     test_event.title = "testTitle";
    //     test_event.description = "testDescription";
    //     test_event.date_time = "2022:12:12";
    //     return test_event;
    // }();
    // std::cout << test_event.toJSON(errc) << std::endl;

    Event from_constructor("title", "2112:12:12", 0, Address("Moscow", 0), "no desc");
    std::cout << "from constructor json " << from_constructor.toJSON(errc) << std::endl;

    return 0;
}