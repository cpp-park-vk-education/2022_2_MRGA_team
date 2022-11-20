#include "networking/TcpServer.hpp"
#include "networking/TcpConnection.hpp"
#include <iostream>

namespace MRGA {
    using boost::asio::ip::tcp;

    TCPServer::TCPServer(IPV ipv, int port) : _ipVersion(ipv), _port(port),
        _acceptor(_ioContext, tcp::endpoint(_ipVersion == IPV::V4 ? tcp::v4() : tcp::v6(), _port)) {


    }

    int TCPServer::Run() {
        try {
            startAccept();
            _ioContext.run();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
        return 0;
    }

    void TCPServer::startAccept() {
        // Create a connection
        auto connection = TCPConnection::Create(_ioContext);

        _connections.push_back(connection);

        // asynchronously accept the connection
        _acceptor.async_accept(connection->getSocket(), [connection, this](const boost::system::error_code error) {
            if (!error) {
                connection->Start();
            }

            startAccept();
        });
    }

    template<typename T>
    void TCPServer::WriteToConnection(int connectionIndex, const T &message) {

    }

    template<typename T>
    void TCPServer::RegisterListenCallback(TCPServer::ListenCallback<T> callback) {

    }
}

