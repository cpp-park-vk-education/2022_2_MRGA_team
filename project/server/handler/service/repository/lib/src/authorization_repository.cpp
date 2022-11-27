#include "authorization_repository.hpp"

AuthorizationRepository::AuthorizationRepository(DbManager &dbm): db_manager(dbm) {}

User AuthorizationRepository::create_user(User user) {
  User created_user;
  return created_user;
}

bool AuthorizationRepository::existence_nickname(std::string nickname) {
  return true;
}
bool AuthorizationRepository::existence_email(std::string email) {
  return true;
}

bool AuthorizationRepository::check_password(size_t user_id,
                                            std::string input_password) {
  return true;
}
