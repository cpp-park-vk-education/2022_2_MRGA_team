#pragma once
#include "IConnector.hpp"
#include "state.h"
#include "deferer.hpp"

#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>

namespace {
    using std::string;
    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace net = boost::asio;
    using tcp = net::ip::tcp;
    using response = http::response<http::dynamic_body>;
    using str_request = http::request<http::string_body>;
    using resolved_result = net::ip::basic_resolver_results<net::ip::tcp>;
};  // namespace




class HttpRequestConnector : public IConnector {
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
    unsigned int version = 11;
    string user_agent = "HttpRequestConnectorLibAgent";

    str_request string_request(const string &target, const http::verb& method = http::verb::get) const;
    void defer_close(Deferrer& def);

    static string body_to_str(beast::multi_buffer const& buffers);




    state _state;

  public:
    HttpRequestConnector(const string& host, const string& port);

    virtual void set_host(const string& new_host) override;
    virtual void set_port(const string& new_port) override;
    virtual void resolve_url() override;
    virtual void resolve_url(const string& host, const string& port) override;

    virtual const string& get_host() const override;
    virtual const string& get_port() const override;

    virtual Response<bool> authorization(const string &login,
                                         const string &password) override;
    virtual Response<bool> registration(const string &login,
                                        const string &password) override;

    void test_request();
};

int test_func(int a, int b);
