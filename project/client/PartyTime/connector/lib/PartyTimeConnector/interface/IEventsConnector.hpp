#pragma once
#include "utils.h"
#include <structs.hpp>
#include <vector>
#include <future>

class IEventsConnector {

    public:

    virtual Response<optional<vector<Event>>> events() = 0;
    virtual future<Response<optional<vector<Event>>>> events_async() = 0;

    virtual Response<optional<vector<Event>>> my_events() = 0;
    virtual Response<optional<vector<Event>>> visiting_events() = 0;

    virtual Response<optional<Event>> visit(const size_t& event_id) = 0;
    virtual Response<optional<Event>> unvisit(const size_t& event_id) = 0;

    virtual Response<optional<Event>> create_event(const Event& event) = 0;
    virtual Response<optional<Event>> update_event(const Event& event) = 0;
    virtual future<Response<optional<Event>>> create_event_async(const Event& event) = 0;

    virtual ~IEventsConnector() = default;
};
