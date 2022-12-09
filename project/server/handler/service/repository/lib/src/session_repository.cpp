#include "session_repository.hpp"

SessionRepository::SessionRepository(DbManager &dbm)
: db_manager(dbm) {}

int SessionRepository::create_token(Token token) {
  return 1;
}
int SessionRepository::delete_token(Token token) {
  return 1;
}

int SessionRepository::check_token(const std::string &token) {
  return 1;
}

User SessionRepository::get_user_by_token(Token token) {
  User user;
  return user;
}
