#pragma once

#include <cstddef>
#include <string>

#include "iuser_repository.hpp"

class UserRepository : public IUserRepository {
 public:
  User get_user_data(size_t user_id);

  void update_user_data(User user);

  void add_visitor(size_t event_id, size_t user_id);

  void delete_visitor(size_t event_id, size_t user_id);
};
