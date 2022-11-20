#include <boost/asio.hpp>
#include <array>
#include <iostream>

using boost::asio::ip::tcp;

enum {PORT_NUMBER = 8080};

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context ioContext;

        tcp::resolver resolver { ioContext };

        tcp::resolver::results_type endPoints = resolver.resolve("127.0.0.1", "8080");

        tcp::socket socket { ioContext };
        boost::asio::connect(socket, endPoints);

        while (true) {
            std::array<char, 4096> buf;

            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof) {
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout.write(buf.data(), len);
        }

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
};