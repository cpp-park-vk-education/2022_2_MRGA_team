#pragma once

#include <cstddef>
#include <string>

#include <structs.hpp>

class IAuthorizationRepository {
 public:
  virtual int create_user(User user) = 0;

  virtual int existence_user(User user) = 0;

};
