#pragma once
#include "utils.h"
#include <structs.hpp>


class IAuthConnector {

    public:
    virtual Response<bool> login(const User& user) = 0;

    virtual Response<bool> signup(const User& user) = 0;

    virtual Response<bool> logout() = 0;

    virtual ~IAuthConnector() = default;
};