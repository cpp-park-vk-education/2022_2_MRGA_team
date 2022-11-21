#pragma once
#include <memory>
#include "IAuthConnector.hpp"
#include "IEventsConnector.hpp"
#include "IUsersConnector.hpp"




class PartyTimeConnector {
    PartyTimeConnector(
            std::shared_ptr<IAuthConnector>& auth,
            std::shared_ptr<IEventsConnector>& events,
            std::shared_ptr<IUsersConnector>& users);
    public:
    std::shared_ptr<IAuthConnector> auth;
    std::shared_ptr<IEventsConnector> events;
    std::shared_ptr<IUsersConnector> users;
    ~PartyTimeConnector() = default;
};