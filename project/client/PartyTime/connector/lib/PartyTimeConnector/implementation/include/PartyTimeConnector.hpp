#pragma once
#include <memory>
#include "IAuthConnector.hpp"
#include "IEventsConnector.hpp"
#include "IUsersConnector.hpp"

namespace {
    using std::shared_ptr;
}


class PartyTimeConnector {
public:
    PartyTimeConnector(shared_ptr<IAuthConnector>& auth, shared_ptr<IEventsConnector>& events, shared_ptr<IUsersConnector>& users);
    shared_ptr<IAuthConnector> auth;
    shared_ptr<IEventsConnector> events;
    shared_ptr<IUsersConnector> users;

    static shared_ptr<PartyTimeConnector> default_implementation(const string& host, const string& port);
    ~PartyTimeConnector() = default;
};