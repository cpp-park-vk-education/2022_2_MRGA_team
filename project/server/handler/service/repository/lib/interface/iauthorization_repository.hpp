#pragma once

#include <cstddef>
#include <string>

#include "objects.hpp"

class IAuthorizationRepository {
public:
  virtual User create_user(User user) = 0;

  virtual bool existence_nickname(std::string nickname) = 0;
  virtual bool existence_email(std::string email) = 0;

  virtual bool check_password(size_t user_id,
                              std::string input_password) = 0;
};
