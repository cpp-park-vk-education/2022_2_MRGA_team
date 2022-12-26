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
    Connection *conn;
    try {
      conn = new Connection(uri);
      DbManager::set_prepare_for_conn(conn);
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
      Connection *conn = new Connection(config_data);
      DbManager::set_prepare_for_conn(conn);
      connections[ i ] = conn;
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

void DbManager::set_prepare_for_conn(Connection *conn) {
  conn->prepare("insert_address_if_need", "INSERT INTO addresses "
    "(address_title, longitude, latitude) VALUES "
    "($1, CASE WHEN $2=0 THEN null ELSE $2 END, "
    "CASE WHEN $3=0 THEN NULL ELSE $3 END) "
    "ON CONFLICT(address_title) DO UPDATE SET "
    "longitude=EXCLUDED.longitude, latitude=EXCLUDED.latitude "
    "RETURNING id;");
  conn->prepare("insert_event", "INSERT INTO events "
    "(title, overview, date_time, max_visitors, user_id, address_id) VALUES "
    "($1, CASE WHEN $2='' THEN null ELSE $2 END, "
    "$3, $4, $5, $6) RETURNING id;");
  conn->prepare("select_events", "SELECT events.id AS events_id, "
                              "events.title AS title, "
                              "coalesce(events.overview, '') AS description, "
                              "events.date_time AS date_time, "
                              "events.max_visitors AS max_visitors, "
                              "events.user_id AS user_id, "
                              "events.address_id AS address_id, "
                              "addresses.address_title AS address, "
                              "coalesce(addresses.longitude, 0) AS longitude, "
                              "coalesce(addresses.latitude, 0) AS latitude, "
                              "coalesce(events.users, '{}') AS users "
                              "FROM events LEFT JOIN addresses "
                              "ON events.address_id = addresses.id "
                              "ORDER BY events.title;");
  conn->prepare("try_to_find_user", "SELECT id, nickname, passcode "
    "FROM users "
    "WHERE nickname = $1 "
    "LIMIT 1;");
  conn->prepare("insert_user", "INSERT INTO users "
    "(nickname, passcode, email, birth_date, overview) VALUES "
    "($1, $2, $3, "
    "CASE WHEN $4=to_date('1300-11-13', 'YYYY-MM-DD') THEN NULL ELSE $4 END, CASE WHEN $5='' THEN NULL ELSE $5 END) "
    "RETURNING id;");
  conn->prepare("try_to_find_user_by_id", "SELECT 200 AS result "
    "FROM users "
    "WHERE id = $1;");
  conn->prepare("get_user_data_by_id", "SELECT nickname, passcode, "
    "email, coalesce(birth_date, '1300-11-13') AS birth_date, "
    "coalesce(overview, '') AS overview, events "
    "FROM users "
    "WHERE id = $1;");
  conn->prepare("insert_new_token", "INSERT INTO tokens "
    "(token_content, expire_date_time, user_id) VALUES "
    "($1, $2, $3) RETURNING id;");
  conn->prepare("try_to_find_token_for_user", "SELECT user_id "
    "FROM tokens "
    "WHERE token_content = $1;");
  conn->prepare("add_user_into_event", "UPDATE events SET "
    "users = array_append(users, $1) "
    "WHERE id = $2;");
  conn->prepare("add_event_into_user", "UPDATE users SET "
    "events = array_append(events, $1) "
    "WHERE id = $2;");
  conn->prepare("remove_user_from_event", "UPDATE events SET "
    "users = array_remove(users, $1) "
    "WHERE id = $2;");
  conn->prepare("remove_event_from_user", "UPDATE users SET "
    "events = array_remove(events, $1) "
    "WHERE id = $2;");
  conn->prepare("update_event", "UPDATE events SET "
    "title = CASE WHEN $1='' THEN null ELSE $1 END, "
    "overview = CASE WHEN $2='' THEN null ELSE $2 END, "
    "date_time = $3, max_visitors = $4, user_id = $5, address_id = $6 WHERE id = $7 RETURNING id;");
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


