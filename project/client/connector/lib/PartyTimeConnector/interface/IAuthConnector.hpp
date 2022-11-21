#pragma once
#include "utils.h"


class IAuthConnector {

    public:
    virtual Response<bool> login(const string &login,
                                        const string &password) = 0;

    virtual Response<bool> signup(const string &login,
                                        const string &password) = 0;

    virtual Response<bool> logout() = 0;

    virtual ~IAuthConnector() = default;
};