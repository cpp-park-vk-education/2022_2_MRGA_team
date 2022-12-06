//#include "http_connection.hpp"
//
//#include <boost/beast/core.hpp>
//#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>
//#include <boost/asio/connect.hpp>
//#include <boost/asio/ip/tcp.hpp>
//#include <cstdlib>
//#include <iostream>
//#include <string>
//
//
//namespace beast = boost::beast;     // from <boost/beast.hpp>
//namespace http = beast::http;       // from <boost/beast/http.hpp>
//namespace net = boost::asio;        // from <boost/asio.hpp>
//using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>
//
//
//void http_server(tcp::acceptor& acceptor, tcp::socket& socket) {
//    acceptor.async_accept(socket,
//          [&](beast::error_code ec)
//          {
//                if (!ec) {
//                    std::make_shared<http_connection>(std::move(socket))->start();
//                }
//              http_server(acceptor, socket);
//          });
//}
//
//int main(int argc, char* argv[])
//{
//    try {
//        if (argc != 3) {
//            std::cerr << "Usage: " << argv[0] << " <address> <port>\n";
//            std::cerr << "  For IPv4, try:\n";
//            std::cerr << "    receiver 0.0.0.0. 80\n";
//            std::cerr << "  For IPv6, try:\n";
//            std::cerr << "    receiver 0::0 80\n";
//            return EXIT_FAILURE;
//        }
//
//        auto const address = net::ip::make_address(argv[1]);
//        auto port = static_cast<unsigned short>(std::atoi(argv[2]));
//
//        net::io_context ioc{1};
//
//        tcp::acceptor acceptor {ioc, {address, port}};
//        tcp::socket socket{ioc};
//        http_server(acceptor, socket);
//
//        ioc.run();
//    }
//
//    catch (std::exception const& e)
//    {
//        std::cerr << "Error: " << e.what() << std::endl;
//        return EXIT_FAILURE;
//    }
//
//    return 0;
//}

#include "server/tcp_server.hpp"

enum { PORT = 8080 };

int main() {
    tcp_server server(IPV::V4, PORT);
    server.run();
}
