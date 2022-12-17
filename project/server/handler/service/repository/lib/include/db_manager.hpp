#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <pqxx/pqxx>

using Connection = pqxx::connection;
using Worker = pqxx::work;
using Result = pqxx::result;

enum result {
  OK,
  ERROR
};

const char path_config[] = {"configs/database.txt"};

struct PGConnectionConfig {

  std::string user;
  std::string password;
  std::string host;
  unsigned int port;
  std::string database;

  static PGConnectionConfig from_file(const std::string &path, result &res);

};

static Connection* PGConnectionByConfig(const PGConnectionConfig& config, result &res);

class DbManager {
 public:
  const size_t MAX_SIZE;
  DbManager(int);
  DbManager();
  DbManager(const PGConnectionConfig& config);
  static DbManager from_config(const PGConnectionConfig& config, result& res);

  Connection *get_free_connection();

  int return_connection(Connection *conn);

  size_t count_connections() const;

  ~DbManager();

 private:
  std::vector<std::string> load_config(const std::string &path) const;
  std::string serialize(const std::vector<std::string> &params) const;
  std::vector<Connection *> connections;
};
