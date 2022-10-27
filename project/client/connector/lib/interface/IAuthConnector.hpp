#pragma once
#include "utils.h"

class IAuthConnector {

    public:

    virtual Response<bool> authorization(const string &login,
                                        const string &password) = 0;

    virtual Response<bool> registration(const string &login,
                                        const string &password) = 0;


    virtual ~IAuthConnector() = default;
};