#include <iostream>

#include "db_manager.hpp"

DbManager::DbManager() {
  connections.resize(1);
  Connection c("dbname = mashadb user = mashapg password = mashapg \
      hostaddr = 127.0.0.1 port = 5432");
  std::cout << c.is_open() << std::endl;
  connections[0] = 3;
}

int DbManager::get_free_connection() {
  return connections[0];
} 

int DbManager::return_connection(int connection) {
  return 1;
}
