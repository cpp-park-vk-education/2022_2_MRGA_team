#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include <boost/asio.hpp>

enum class IPV {
    V4,
    V6
};

class tcp_server {
public:
    tcp_server(IPV ipv, unsigned short port);

    int run();
private:
    IPV ip_version_;
    unsigned short port_;

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
};


#endif //SERVER_SERVER_HPP
