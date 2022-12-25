#include "authorization_repository.hpp"

AuthorizationRepository::AuthorizationRepository(DbManager &dbm)
: db_manager(dbm) {}

int AuthorizationRepository::create_user(User user) {
  
  return 1;
}

int AuthorizationRepository::existence_nickname(const std::string &nickname) {
  return true;
}
int AuthorizationRepository::existence_email(const std::string &email) {
  return true;
}

int AuthorizationRepository::check_password(size_t user_id,
                                    const std::string &input_password) {
  return true;
}
