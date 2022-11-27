#pragma once

#include <vector>
// #include <pqxx/pqxx>

using Connection = int;

class DbManager {
 public:
  DbManager();

  Connection get_free_connection();

 private:
  std::vector<Connection> connections;
};
