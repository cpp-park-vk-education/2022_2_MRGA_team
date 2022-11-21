#pragma once

#include <cstddef>
#include <string>

#include "isession_repository.hpp"

class SessionRepository {
 public:
  Token create_token(size_t user_id);
  void delete_token(Token token);
  std::vector<Token> get_tokens(size_t user_id);
};
