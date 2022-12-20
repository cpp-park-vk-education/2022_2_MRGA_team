#pragma once
#include "utils.h"
#include <structs.hpp>

class IUsersConnector {

    public:

    virtual Response<User> profile(const size_t& id) = 0;

    virtual Response<bool> setting(const User& user) = 0;

    virtual ~IUsersConnector() = default;
};