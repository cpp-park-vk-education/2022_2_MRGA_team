#pragma once
#include "IAuthConnector.hpp"
#include "IConnector.hpp"
#include "IEventsConnector.hpp"
#include "IUsersConnector.hpp"

class IPartyTimeConnector: public IConnector, IAuthConnector, IEventsConnector, IUsersConnector {

    public:

    virtual ~IPartyTimeConnector() override {}

};