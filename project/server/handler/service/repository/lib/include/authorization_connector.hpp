#pragma once

#include <cstddef>
#include <string>

#include "iauthorization_connector.hpp"

class AuthorizationConnector : public IAuthorizationConnector {
  Profile create_profile(Profile profile);

  bool existence_nickname(std::string nickname);
  bool existence_email(std::string email);

  Profile get_profile_data(size_t profile_id);

  void update_nickname(size_t profile_id, std::string new_nickname);
  void update_email(size_t profile_id, std::string new_email);
  void update_password(size_t profile_id, std::string new_password);
  void update_description(size_t profile_id, std::string new_description);

  bool check_password(size_t profile_id, std::string input_password);

  void delete_profile(size_t profile_id);

  Token create_token(size_t profile_id);
  void delete_token(size_t profile_id);
  std::string get_expiration_date_time(size_t profile_id);  // Удаляю токен при устаревании
};
