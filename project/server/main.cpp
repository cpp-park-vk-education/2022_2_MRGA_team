#include "http_connection.hpp"
#include "tcp_server.hpp"

enum { PORT = 8080 };

int main() {
    tcp_server server(IPV::V4, PORT);
    server.run();
}
