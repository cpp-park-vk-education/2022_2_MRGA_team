#pragma once
#include "utils.h"
#include <structs.hpp>
#include <vector>
#include <future>

class IEventsConnector {

    public:

    virtual Response<optional<vector<Event>>> events() = 0;
    virtual future<Response<optional<vector<Event>>>> events_async() = 0;

    virtual Response<bool> visit(const size_t& event_id, const size_t& user_id) = 0;

    virtual Response<optional<Event>> create_event(const Event& event) = 0;
    virtual future<Response<optional<Event>>> create_event_async(const Event& event) = 0;

    virtual ~IEventsConnector() = default;
};
