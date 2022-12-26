#pragma once

#include <cstddef>
#include <string>

#include "iauthorization_repository.hpp"
#include "db_manager.hpp"

class AuthorizationRepository : public IAuthorizationRepository {
 public:
  explicit AuthorizationRepository(DbManager &dbm);

  /* Возвращается положительный id, если успешно created, 
  иначе отрицательная ошибка */
  int create_user(User user);

  /* Возвращается
    положительное число - id, совпадение и nickname, и password)
    -2 - password не совпадает
    -3 - если не найден user c таким nickname, то есть user'а такого нет
    иначе другое отрицательное число - ошибка при работе с БД */
  int existence_user(User user);

 private:
  DbManager &db_manager;
};
