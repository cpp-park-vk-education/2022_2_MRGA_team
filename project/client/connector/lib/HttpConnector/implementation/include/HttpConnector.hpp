#ifndef CONNECTOR_HTTP_CONNECTOR_HPP
#define CONNECTOR_HTTP_CONNECTOR_HPP
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include "IHttpConnector.hpp"
#include "deferer.h"


namespace {
    using std::string;
    using namespace std::string_literals;
    namespace beast       = boost::beast;
    namespace http        = beast::http;
    namespace net         = boost::asio;
    using tcp             = net::ip::tcp;
    using Response        = http::response<http::dynamic_body>;
    using str_request     = http::request<http::string_body>;
    using resolved_result = net::ip::basic_resolver_results<net::ip::tcp>;
};

class HttpConnector: IHttpConnector {

private:
    // base data
    string host;
    string port;
    resolved_result url;

    // for network
    net::io_context ioc;
    tcp::resolver resolver;
    beast::tcp_stream stream;
    beast::flat_buffer buffer;
    const unsigned int version = 11;
    string user_agent = "HttpRequestConnectorLibAgent";

    void defer_close(Deferrer &def);
    [[nodiscard]]
    str_request string_request(const string &target,
                               const string &method) const;

    static string body_to_str(beast::multi_buffer const &buffers);

public:

    HttpConnector(const string &host, const string &port);

    void set_host(const string& new_host) override;
    void set_port(const string& new_port) override;
    void resolve_url() override;
    void resolve_url(const string& host, const string& port) override;
    [[nodiscard]] const string& get_host() const override;
    [[nodiscard]] const string& get_port() const override;

    optional<HTTPResponse<string>> GET(
            const string& target,
            const optional<unordered_map<name, value>>& headers) override;

    optional<HTTPResponse<string>> POST(
            const string& target,
            const string& body,
            const optional<unordered_map<name, value>>& headers) override;

    ~HttpConnector() {}
};

#endif //CONNECTOR_HTTP_CONNECTOR_HPP