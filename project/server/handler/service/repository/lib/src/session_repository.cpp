#include "session_repository.hpp"

Token SessionRepository::create_token(size_t user_id) {
  Token token;
  return token;
}
void SessionRepository::delete_token(Token token) {}

std::vector<Token> SessionRepository::get_tokens(size_t user_id) {
  return {};
}
