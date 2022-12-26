#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "isession_repository.hpp"
#include "db_manager.hpp"

class SessionRepository : public ISessionRepository {
 public:
  explicit SessionRepository(DbManager &dbm);
  /* Во входной структуре Token обязательно:
    token, id пользователя
  Возврат:
    отрицательного числа - если что-то случилось,
    положительного числа - user_id входящего пользователя, созданного в бд */
  int create_token(Token token);
  int delete_token(Token token);

  /* Возвращается
    положительное число - id пользователя
    -2 - если такого токена нет в бд
    иначе другое отрицательное число - ошибка при работе с БД */
  int check_token(const std::string &token);
  // User get_user_by_token(Token token);
 private:
  DbManager &db_manager;
};
