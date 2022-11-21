#pragma once

#include <cstddef>
#include <string>

#include "objects.hpp"

class IUserRepository {
public:
  virtual User get_user_data(size_t user_id) = 0;

  virtual void update_user_data(User user) = 0;

  virtual void add_visitor(size_t event_id, size_t user_id) = 0;

  virtual void delete_visitor(size_t event_id, size_t user_id) = 0;
};
