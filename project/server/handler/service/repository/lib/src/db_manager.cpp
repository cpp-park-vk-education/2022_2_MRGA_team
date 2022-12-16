#include "db_manager.hpp"
#include <cstdlib>
static int counter = 0;

DbManager::DbManager() : MAX_SIZE(10) {
  connections.resize(MAX_SIZE);
  auto p = "configs/database.txt";
  // const char path_config[] = {"../configs/database.txt"};
  std::vector<std::string> params = load_config(p);
  std::cout << "our p" <<std::string(p) << std::endl;
  std::string config_data(serialize(params));
  for (size_t i = 0; i < MAX_SIZE; ++i) {
    std::cout << config_data << std::endl;
    connections[i] = new Connection(config_data);
    // connections[i] = new Connection("postgresql://mashapg:mashapg@0.0.0.0:5432/mashadb");
    // "postgresql://accounting@localhost/company"
  }
}

size_t DbManager::count_connections() const {
  return connections.size();
}
// postgresql://mashapg:mashapg@10.0.0.10:5432/mashadb
std::vector<std::string> DbManager::load_config(const std::string &path) const {
  ++counter;
  std::ifstream in_conf(path);
  std::cout << path << std::endl;
  system("pwd");
  system("cd configs && ls");
  std::vector<std::string> arr(5);
  // arr[0] = "mashapg";
  // arr[1] = "mashapg";
  // arr[2] = "0.0.0.0";
  // arr[3] = "5432";
  // arr[4] = "mashadb";
  size_t i = 0;
  std::cerr << "ФАЙЛ ОТКРЫТ? " <<  in_conf.is_open() << std::endl;
  if (in_conf.is_open()) {
    for (std::string line; std::getline(in_conf, line); ) {
      char delimiter = '=';
      std::cout <<"line"<< line << std::endl;
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
    conn->close();
    delete conn;
    connections.pop_back();
  }
}
