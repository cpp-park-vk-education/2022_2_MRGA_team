#include "db_manager.hpp"
#include <cstdlib>

DbManager::DbManager() : MAX_SIZE(10) {
    std::cout << "ВЫЗОВ КОНСТРУКТОРА DB MANAGER" << std::endl;
  connections.resize(MAX_SIZE);
  std::vector<std::string> params = load_config(path_config);
  std::string config_data(serialize(params));
  for (size_t i = 0; i < MAX_SIZE; ++i) {
    connections[i] = new Connection(config_data);
  }
  load_config(path_config);
}

size_t DbManager::count_connections() const {
  return connections.size();
}
// postgresql://mashapg:mashapg@10.0.0.10:5432/mashadb
std::vector<std::string> DbManager::load_config(const std::string &path) const {
  std::ifstream in_conf(path_config);
  std::vector<std::string> arr(5);
  // arr[0] = "mashapg";
  // arr[1] = "mashapg";
  // arr[2] = "10.0.0.10";
  // arr[3] = "5432";
  // arr[4] = "mashadb";
  system("pwd");
  size_t i = 0;
  std::cout << "Файл открыт? ";
  if (!in_conf.is_open()) {
    std::cout << "нет, не открыт" << std::endl;
  } else {
    std::cout << "да, открыт" << std::endl;
  }
  if (in_conf.is_open()) {
    for (std::string line; std::getline(in_conf, line); ) {
      std::cout << "ЧАСТЬ КОНФИГА" << line << std::endl;
      char delimiter = '=';
      std::string token = line.substr(line.find(delimiter) + 1, line.length());
      arr[i++] = token;
    }
  }
  in_conf.close();
  return arr;
}

std::string DbManager::serialize(const std::vector<std::string> &params) const {
  std::string res = "postgresql://" + params[0] +
    ":" + params[1] + "@" + params[2] + ":" + params[3] + "/" + params[4];
  return res;
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
