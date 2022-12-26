#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include <boost/asio.hpp>
#include <string>

#include "db_manager.hpp"
#include "service.hpp"



enum class IPV {
    V4,
    V6
};

class tcp_server {
public:
    tcp_server(const std::string &host, unsigned short port);

    int run(ServiceManager &service_manager);
private:
    IPV ip_version_;
    unsigned short port_;

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
};


#endif //SERVER_SERVER_HPP
