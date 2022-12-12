#pragma once

#include <cstddef>
#include <string>

#include "iuser_repository.hpp"
#include "db_manager.hpp"

class UserRepository : public IUserRepository {
 public:
  explicit UserRepository(DbManager &dbm);
  int existence_user(size_t user_id);
  User get_user_data(size_t user_id);

  int update_user_data(User user);

  int add_visitor(size_t event_id, size_t user_id);

  int delete_visitor(size_t event_id, size_t user_id);
 private:
  DbManager &db_manager;
};
