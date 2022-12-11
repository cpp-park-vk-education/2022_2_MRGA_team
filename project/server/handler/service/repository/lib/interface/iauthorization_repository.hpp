#pragma once

#include <cstddef>
#include <string>

#include "../../../json_struct_mapping_lib/structs.hpp"

class IAuthorizationRepository {
 public:
  virtual User create_user(User user) = 0;

  virtual int existence_nickname(const std::string &nickname) = 0;
  virtual int existence_email(const std::string &email) = 0;

  virtual int check_password(size_t user_id,
                          const std::string &input_password) = 0;
};
