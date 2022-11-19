#include "authorization_connector.hpp"

Profile AuthorizationConnector::create_profile(Profile profile) {
  Profile created_profile;
  return created_profile;
}

bool AuthorizationConnector::existence_nickname(std::string nickname) {
  return true;
}
bool AuthorizationConnector::existence_email(std::string email) {
  return true;
}

Profile
AuthorizationConnector::get_profile_data(size_t profile_id) {
  Profile profile;
  return profile;
}

void AuthorizationConnector::update_nickname(size_t profile_id,
                                             std::string new_nickname) {}
void AuthorizationConnector::update_email(size_t profile_id,
                                          std::string new_email) {}
void AuthorizationConnector::update_password(size_t profile_id,
                                             std::string new_password) {}
void AuthorizationConnector::update_description(size_t profile_id,
                                                std::string new_description) {}

bool AuthorizationConnector::check_password(size_t profile_id,
                                            std::string input_password) {
  return true;
}

void AuthorizationConnector::delete_profile(size_t profile_id) {}

void AuthorizationConnector::create_token(size_t profile_id) {}
void AuthorizationConnector::delete_token(size_t profile_id) {}
bool AuthorizationConnector::is_actual_token(size_t profile_id) {
  return true;
}
