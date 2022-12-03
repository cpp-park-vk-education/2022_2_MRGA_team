#include "db_manager.hpp"

DbManager::DbManager() {
  connections.resize(20);
}

Connection DbManager::get_free_connection() {
  return 1;
}

int DbManager::return_connection(Connection connection) {
  return 1;
}
