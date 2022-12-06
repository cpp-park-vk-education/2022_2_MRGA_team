#include "user_repository.hpp"

UserRepository::UserRepository(DbManager &dbm):db_manager(dbm) {}

User UserRepository::get_user_data(size_t user_id) {
  User user;
  return user;
}

int UserRepository::update_user_data(User user) {
  return 1;
}

int UserRepository::add_visitor(size_t event_id, size_t user_id) {
  return 1;
}

int UserRepository::delete_visitor(size_t event_id, size_t user_id) {
  return 1;
}
