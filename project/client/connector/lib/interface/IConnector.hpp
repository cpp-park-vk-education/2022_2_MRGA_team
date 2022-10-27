#pragma once
#include "utils.h"

class IConnector {
    public:

    virtual void set_host(const string& new_host) = 0;
    virtual void set_port(const string& new_port) = 0;
    virtual void resolve_url() = 0;
    virtual void resolve_url(const string& host, const string& port) = 0;

    virtual const string& get_host() const = 0;
    virtual const string& get_port() const = 0;

    virtual ~IConnector() = default;
};
