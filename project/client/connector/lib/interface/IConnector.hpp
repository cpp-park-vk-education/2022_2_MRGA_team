#pragma once
#include <string>
#include <boost/beast/core.hpp>

namespace {
    using std::string;
    using boost::beast::error_code;
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

    virtual void set_host(const string& new_host) = 0;
    virtual void set_port(const string& new_port) = 0;
    virtual void resolve_url() = 0;
    virtual void resolve_url(const string& host, const string& port) = 0;

    virtual const string& get_host() const = 0;
    virtual const string& get_port() const = 0;
};
