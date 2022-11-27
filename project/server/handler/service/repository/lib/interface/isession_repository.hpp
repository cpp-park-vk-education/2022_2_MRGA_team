#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "objects.hpp"

class ISessionRepository {
 public:
  virtual Token create_token(size_t user_id) = 0;
  virtual int delete_token(Token token) = 0;
  virtual std::vector<Token> get_tokens(size_t user_id) = 0;
};
