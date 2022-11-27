#pragma once

#include <cstddef>
#include <string>

#include "iauthorization_repository.hpp"
#include "db_manager.hpp"

class AuthorizationRepository : public IAuthorizationRepository {
 public:
  explicit AuthorizationRepository(DbManager &dbm);

  User create_user(User user);

  bool existence_nickname(const std::string &nickname);
  bool existence_email(const std::string &email);

  bool check_password(size_t user_id, const std::string &input_password);
 private:
  DbManager &db_manager;
};
