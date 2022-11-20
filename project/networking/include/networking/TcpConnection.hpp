#ifndef NETWORKING_TCPCONNECTION_HPP
#define NETWORKING_TCPCONNECTION_HPP

#include <boost/asio.hpp>
#include <memory>

namespace MRGA {
    using boost::asio::ip::tcp;
class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
    public:
        using pointer = std::shared_ptr<TCPConnection>;

        static pointer Create(boost::asio::io_context &ioContext) {
            return pointer(new TCPConnection(ioContext));
        }

        tcp::socket &getSocket() { return _socket; }

        void Start();
    private:
        explicit TCPConnection(boost::asio::io_context &ioContext);
    private:
        tcp::socket  _socket;
        std::string _message {"Hello, I'm the server!\n"};
    };
}



#endif //NETWORKING_TCPCONNECTION_HPP
