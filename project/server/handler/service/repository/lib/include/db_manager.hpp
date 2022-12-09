#pragma once

#include <vector>
#include <pqxx/pqxx>

using Connection = pqxx::connection;

class DbManager {
 public:
  DbManager();

  int get_free_connection();

  int return_connection(int connection);

 private:
  std::vector<int> connections;
};
