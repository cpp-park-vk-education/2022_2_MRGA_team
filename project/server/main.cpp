#include "http_connection.hpp"
#include "tcp_server.hpp"
#include "db_manager.hpp"

int main(int argc, char* argv[]) {
    const std::string path_config = "configs/database.txt";
    std::string HOST = "0.0.0.0";
    unsigned short PORT = 8081;
    if (argc >= 3) {
        HOST = std::string(argv[1]);
        PORT = std::stoi(argv[2]);
        std::cout << "HOST " << HOST << std::endl;
        std::cout << "PORT " << PORT << std::endl;
    }
    result parse_result;
    auto config = PGConnectionConfig::from_file(path_config, parse_result);
    if (parse_result != OK) {
        std::abort();
    }
    if (argc >= 5) {
        config.host = std::string(argv[3]);
        config.port = std::stoi(argv[4]);
        std::cout << "dbHost " << config.host << std::endl;
        std::cout << "dbPort " << config.port  << std::endl;
    }
    DbManager manager = DbManager::from_config(config, parse_result);
    if (parse_result != OK) {
        std::abort();
    }
    std::cout << "==========СЕРВЕР ЗАПУСТИЛСЯ===========" << std::endl;
    ServiceManager serviceManager(manager);

    tcp_server server(HOST, PORT);
    server.run(serviceManager);
    std::cerr << "==========СЕРВЕР УПАЛ===========" << std::endl;
}
