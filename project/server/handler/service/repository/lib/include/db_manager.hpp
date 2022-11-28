#pragma once

#include <vector>
// #include <pqxx/pqxx>

using Connection = int;

class DbManager {
 public:
  DbManager();

  Connection get_free_connection();

  int return_connection(Connection connection);

 private:
  std::vector<Connection> connections;
};
