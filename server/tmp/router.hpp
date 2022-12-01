#ifndef PROJECT_ROUTER_HPP
#define PROJECT_ROUTER_HPP

#include <map>
#include <string>
#include <functional>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>


namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>


class router {
    std::map<std::string, std::function<void()>> get_handler;
    std::map<std::string, std::function<void()>> post_handler;
    std::map<std::string, std::function<void()>> put_handler;
    std::map<std::string, std::function<void()>> delete_handler;
public:
    router() = default;

    void handle_req();
};


#endif //PROJECT_ROUTER_HPP
