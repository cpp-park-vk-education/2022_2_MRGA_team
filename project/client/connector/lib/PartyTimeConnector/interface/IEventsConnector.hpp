#pragma once
#include "utils.h"
#include "objects.hpp"

class IEventsConnector {

    public:

    virtual Response<optional<vector<Event>>> events(optional<QueryParams> = std::nullopt) = 0;
    virtual Response<bool> visit(const size_t& event_id, const size_t& user_id) = 0;
    virtual Response<optional<Event>> create_event(const Event& event) = 0;



    virtual ~IEventsConnector() = default;
};