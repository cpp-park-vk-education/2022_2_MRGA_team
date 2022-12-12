#include "db_manager.hpp"

DbManager::DbManager() : MAX_SIZE(10) {
    std::cout << "ВЫЗОВ КОНСТРУКТОРА DB MANAGER" << std::endl;
  connections.resize(MAX_SIZE);
  // std::string config_data(load_config(path_config));
  for (size_t i = 0; i < MAX_SIZE; ++i) {
    // std::cout << config_data << std::endl;
    // connections[i] = new Connection(config_data);
    connections[i] = new Connection("postgresql://mashapg:mashapg@10.0.0.10:5432/mashadb");
    // "postgresql://accounting@localhost/company"
  }
}

size_t DbManager::count_connections() const {
  return connections.size();
}

std::string DbManager::load_config(const std::string &path) const {
  std::string config;
  std::ifstream in_conf(path_config);
  if (in_conf.is_open()) {
    getline(in_conf, config);
  }
  in_conf.close();
  return config;
}

Connection *DbManager::get_free_connection() {
  if (connections.size() == 0) {
    return nullptr;
  }
  Connection *res = connections.back();
  connections.pop_back();
  return res;
}

int DbManager::return_connection(Connection *conn) {
  if (!conn) {
    return 0;
  }
  connections.push_back(conn);
  return 1;
}

DbManager::~DbManager() {
  while(!connections.empty()) {
    Connection *conn = connections.back();
    //conn->close();
    delete conn;
    connections.pop_back();
  }
}
