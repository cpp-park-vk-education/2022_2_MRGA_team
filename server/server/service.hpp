#ifndef PROJECT_SERVICE_HPP
#define PROJECT_SERVICE_HPP


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


class service {
public:
    virtual int handle(boost::string_view target, http::response<http::dynamic_body> &response) = 0;
};

class auth_service : public service {
    int handle(boost::string_view target, http::response<http::dynamic_body> &response) override;
};

class events_service : public service {
    int handle(boost::string_view target, http::response<http::dynamic_body> &response) override;
};

class users_service : public service {
    int handle(boost::string_view target, http::response<http::dynamic_body> &response) override;
};


#endif //PROJECT_SERVICE_HPP
