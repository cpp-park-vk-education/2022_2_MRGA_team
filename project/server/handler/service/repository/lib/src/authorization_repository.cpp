#include "authorization_repository.hpp"

AuthorizationRepository::AuthorizationRepository(DbManager &dbm)
: db_manager(dbm) {}

int AuthorizationRepository::create_user(User user) {
  int res = 0;
  try {
    Connection *conn = db_manager.get_free_connection();

    try {
      Worker worker(*conn);
      size_t user_id = 0;
      Result result_insert_user = worker.exec_prepared("insert_user",
        user.nickname, user.password, user.email, ((user.birth_date == "") ? "1300-11-13" : user.birth_date),
        user.description);
      if (!result_insert_user.empty()) {
        user_id = result_insert_user.begin()["id"].as<size_t>();
      } else {
        res = -1;
      }
      res = user_id;
      worker.commit();
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      res = -1;
    }
    if (res < 0) {
      db_manager.return_connection(conn);
      return res;
    }

    db_manager.return_connection(conn);

  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    res = -1;
  }
  return res;
}

int AuthorizationRepository::existence_user(User user) {
  int res = 0;
  try {
    Connection *conn = db_manager.get_free_connection();
    
    try {
      Worker worker(*conn);
      Result result_select_user = worker.exec_prepared("try_to_find_user",
        user.nickname);
      if (!result_select_user.empty()) {
        size_t got_id = result_select_user.begin()["id"].as<size_t>();
        std::string got_nickname = result_select_user.begin()["nickname"].as<std::string>();
        std::string got_password = result_select_user.begin()["passcode"].as<std::string>();
        if (got_password == user.password) {
          res = got_id;
        } else if (got_password != user.password) {
          res = -2;
        } else {
          res = -1;
        }
      } else {
        res = -3;
      }
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      res = -1;
    }

    if (res < 0 && res != -2 && res != -3) {
      db_manager.return_connection(conn);
      return res;
    }

    db_manager.return_connection(conn);
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    res = -1;
  }
  return res;
}
