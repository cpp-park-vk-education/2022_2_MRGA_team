#include "http_connection.hpp"
#include "tcp_server.hpp"

enum { PORT = 8080 };

int main() {
    std::cerr << "==========СЕРВЕР ЗАПУСТИЛСЯ===========" << std::endl;
    tcp_server server(IPV::V4, PORT);
    server.run();
    std::cerr << "==========СЕРВЕР УПАЛ===========" << std::endl;
}
