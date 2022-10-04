#pragma once
#include <string>

namespace {
    using std::string;
};

enum class error_code {
    success = 0,

};

template <typename T> struct Response {
    T body;
    error_code result;
};

class IConnector {
    virtual Response<bool> authorization(const string &login,
                                         const string &password) = 0;

    virtual Response<bool> registration(const string &login,
                                        const string &password) = 0;
};
