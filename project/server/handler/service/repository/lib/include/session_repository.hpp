#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "isession_repository.hpp"
#include "db_manager.hpp"

class SessionRepository : public ISessionRepository {
 public:
  explicit SessionRepository(DbManager &dbm);
  Token create_token(size_t user_id);
  void delete_token(Token token);
  std::vector<Token> get_tokens(size_t user_id);
 private:
  DbManager &db_manager;
};
