#pragma once

#include <cstddef>
#include <string>

#include "objects.hpp"

class IAuthorizationConnector {
public:
  virtual Profile create_profile(Profile profile) = 0;

  virtual bool existence_nickname(std::string nickname) = 0;
  virtual bool existence_email(std::string email) = 0;

  virtual Profile get_profile_data(size_t profile_id) = 0;

  virtual void update_nickname(size_t profile_id,
                               std::string new_nickname) = 0;
  virtual void update_email(size_t profile_id, std::string new_email) = 0;
  virtual void update_password(size_t profile_id,
                               std::string new_password) = 0;
  virtual void update_description(size_t profile_id,
                                  std::string new_description) = 0;

  virtual bool check_password(size_t profile_id,
                              std::string input_password) = 0;

  virtual void delete_profile(size_t profile_id) = 0;

  virtual Token create_token(size_t profile_id) = 0;
  virtual void delete_token(size_t profile_id) = 0;
  virtual std::string get_expiration_date_time(size_t profile_id) = 0;
};
