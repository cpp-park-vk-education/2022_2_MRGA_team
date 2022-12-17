#include "db_manager.hpp"
#include <cstdlib>

PGConnectionConfig PGConnectionConfig::from_file(const std::string &path, result &res) {

  std::ifstream in_conf(path);
  PGConnectionConfig config;
  if (!in_conf.is_open()) {
    res = ERROR;
    return config;
  }
  std::string line;
  char delimiter = '=';


  std::getline(in_conf, line);
  config.user = line.substr(line.find(delimiter) + 1, line.length());

  std::getline(in_conf, line);
  config.password = line.substr(line.find(delimiter) + 1, line.length());

  std::getline(in_conf, line);
  config.host = line.substr(line.find(delimiter) + 1, line.length());

  std::getline(in_conf, line);
  config.port = std::stoi(line.substr(line.find(delimiter) + 1, line.length()));

  std::getline(in_conf, line);
  config.database = line.substr(line.find(delimiter) + 1, line.length());

  res = OK;
  return config;

}


Connection* PGConnectionByConfig(const PGConnectionConfig& config, result &res) {
    std::string uri = "postgresql://" + config.user +
    ":" + config.password + "@" + config.host + ":" + std::to_string(config.port) + "/" + config.database;
    Connection* conn;
    try {
      conn = new Connection(uri);
    } catch(...) {
      res = ERROR;
      return nullptr;
    }
    return conn;
}

DbManager::DbManager(int n):MAX_SIZE(n) {}

DbManager::DbManager() : MAX_SIZE(10) {
    connections.resize(MAX_SIZE);

    std::vector<std::string> params = load_config(path_config);
    std::string config_data(serialize(params));
    for (size_t i = 0; i < MAX_SIZE; ++i) {
        connections[ i ] = new Connection(config_data);
    }
    std::cout << "соединения успешно созданы default" << std::endl;
}

DbManager::DbManager(const PGConnectionConfig &config): MAX_SIZE(10){
  connections.resize(MAX_SIZE);
  result res = OK;
  for (auto& conn: connections) {
    conn = PGConnectionByConfig(config, res);
    if (res != OK) {
      throw "Не удалось подключиться к базе данных";
      std::cout << "come error" << std::endl;
    }
  }
  std::cout << "соединения успешно созданы" << std::endl;
}

DbManager DbManager::from_config(const PGConnectionConfig &config, result& res) try {
  DbManager manager(config);
  res = OK;
  return manager;
} catch (std::exception &e){
  std::cout << e.what() << std::endl;
  res = ERROR;
  return DbManager(0);
} catch(...) {
  std::cout << "ошибка при создании" << std::endl;
  res = ERROR;
  return DbManager(0);
}

size_t DbManager::count_connections() const {
  return connections.size();
}
std::vector<std::string> DbManager::load_config(const std::string &path) const {
  std::ifstream in_conf(path);
  system("pwd");
  std::vector<std::string> arr(5);

  size_t i = 0;
  if (in_conf.is_open()) {
    for (std::string line; std::getline(in_conf, line); ) {
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
    conn->close();
    delete conn;
    connections.pop_back();
  }
}


