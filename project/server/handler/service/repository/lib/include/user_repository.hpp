#pragma once

#include <cstddef>
#include <string>

#include "iuser_repository.hpp"
#include "db_manager.hpp"

class UserRepository : public IUserRepository {
 public:
  UserRepository(DbManager &dbm);
  User get_user_data(size_t user_id);

  void update_user_data(User user);

  void add_visitor(size_t event_id, size_t user_id);

  void delete_visitor(size_t event_id, size_t user_id);
 private:
  DbManager &db_manager;
};
