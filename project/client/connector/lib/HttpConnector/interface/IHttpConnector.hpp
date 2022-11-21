#ifndef CONNECTOR_I_HTTP_CONNECTOR_HPP
#define CONNECTOR_I_HTTP_CONNECTOR_HPP
#include <string>
#include <unordered_map>
#include <optional>

namespace {
    using std::string;
    using namespace std::string_literals;
    using std::unordered_map;
    using name = string;
    using value = string;
    using std::optional;
};  // namespace

struct Status {
    unsigned int code;
    string str;
};
template <typename T> struct HTTPResponse {
    HTTPResponse(const T& body, const unordered_map<name, value>& headers, const Status& status)
    :
    response_body(body), headers(headers), status(status) {}

    T response_body;
    unordered_map<name, value> headers;
    Status status;

};


class IHttpConnector {
    public:

    virtual void set_host(const string& new_host) = 0;
    virtual void set_port(const string& new_port) = 0;
    virtual void resolve_url() = 0;
    virtual void resolve_url(const string& host, const string& port) = 0;
    [[nodiscard]] virtual const string& get_host() const = 0;
    [[nodiscard]] virtual const string& get_port() const = 0;


    virtual optional<HTTPResponse<string>> GET(
            const string& target,
            const optional<unordered_map<name, value>>& headers) = 0;

    virtual optional<HTTPResponse<string>> POST(
            const string& target,
            const string& body,
            const optional<unordered_map<name, value>>& headers) = 0;

    virtual ~IHttpConnector() {}
};


#endif //CONNECTOR_I_HTTP_CONNECTOR_HPP
