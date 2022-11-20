#include "networking/TcpServer.hpp"

enum {PORT_NUMBER = 8080};

int main(int argc, char* argv[]) {

    MRGA::TCPServer server(MRGA::IPV::V4, PORT_NUMBER);

    server.Run();

    return 0;
}