#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "objects.hpp"

class ISessionRepository {
 public:
  virtual int create_token(Token token) = 0;
  virtual int delete_token(Token token) = 0;

  virtual int check_token(const std::string &token) = 0;
  virtual User get_user_by_token(Token token) = 0;
};
