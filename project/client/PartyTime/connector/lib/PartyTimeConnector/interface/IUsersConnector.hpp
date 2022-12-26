#pragma once
#include "utils.h"
#include <structs.hpp>

class IUsersConnector {

    public:

    virtual Response<User> profile() = 0;

    virtual Response<User> setting(const User& user) = 0;

    virtual ~IUsersConnector() = default;
};