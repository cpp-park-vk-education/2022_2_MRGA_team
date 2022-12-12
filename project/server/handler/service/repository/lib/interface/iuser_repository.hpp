#pragma once

#include <cstddef>
#include <string>

#include "../../../json_struct_mapping_lib/structs.hpp"

class IUserRepository {
 public:
  virtual int existence_user(size_t user_id) = 0;
  virtual User get_user_data(size_t user_id) = 0;

  virtual int update_user_data(User user) = 0;

  virtual int add_visitor(size_t event_id, size_t user_id) = 0;
  virtual int delete_visitor(size_t event_id, size_t user_id) = 0;
};
