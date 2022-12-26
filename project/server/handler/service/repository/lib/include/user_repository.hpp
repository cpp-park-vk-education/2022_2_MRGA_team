#pragma once

#include <cstddef>
#include <string>

#include "iuser_repository.hpp"
#include "db_manager.hpp"

class UserRepository : public IUserRepository {
 public:
  explicit UserRepository(DbManager &dbm);

  /*
  Возврат:
   1 - если существует,
   0 - если не существует,
   отрицательное число - если ошибка в БД
  */
  int existence_user_by_id(size_t user_id);
  User get_user_data(size_t user_id);

  int update_user_data(User user);

  /*
  Возврат:
   1 - если успешно добавился,
   отрицательное число - если ошибка в БД
  */
  int add_visitor(size_t event_id, size_t user_id);
  /*
  Не идет проверка, если такие id. Просто тогда ничего не произойдет.
  Возврат:
   1 - если успешно удалился,
   отрицательное число - если ошибка в БД
  */
  int delete_visitor(size_t event_id, size_t user_id);
 private:
  DbManager &db_manager;
};
