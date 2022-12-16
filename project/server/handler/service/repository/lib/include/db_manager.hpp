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

const char path_config[] = {"../../configs/database.txt"};

class DbManager {
 public:
  const size_t MAX_SIZE;

  DbManager();

  Connection *get_free_connection();

  int return_connection(Connection *conn);

  size_t count_connections() const;

  ~DbManager();

 private:
  std::vector<std::string> load_config(const std::string &path) const;
  std::string serialize(const std::vector<std::string> &params) const;
  std::vector<Connection *> connections;
};
