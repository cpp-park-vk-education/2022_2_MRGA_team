#ifndef SERVER_HTTP_CONNECTION_HPP
#define SERVER_HTTP_CONNECTION_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

#include "service.hpp"


namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>


class http_connection : public std::enable_shared_from_this<http_connection> {
public:
    explicit http_connection(tcp::socket socket, ServiceManager &service_manager)
            : socket_(std::move(socket)), service_manager_ref_(service_manager) {}

    void start() {
        read_request();
        check_deadline();
    }

private:
    tcp::socket socket_;

    beast::flat_buffer buffer_{8192};

    http::request<http::dynamic_body> request_;

    http::response<http::dynamic_body> response_;

    net::steady_timer deadline_ {
        socket_.get_executor(), std::chrono::seconds(60)
    };

    ServiceManager &service_manager_ref_;

    void read_request();

    void process_request();

    void create_response();

    void write_response();

    void check_deadline();
};

#endif //SERVER_HTTP_CONNECTION_HPP
