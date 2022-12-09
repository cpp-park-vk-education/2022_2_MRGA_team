#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "isession_repository.hpp"
#include "db_manager.hpp"

class SessionRepository : public ISessionRepository {
 public:
  explicit SessionRepository(DbManager &dbm);
  int create_token(Token token);
  int delete_token(Token token);

  int check_token(const std::string &token);
  User get_user_by_token(Token token);
 private:
  DbManager &db_manager;
};
