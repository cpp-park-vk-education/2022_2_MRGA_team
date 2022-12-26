#include "session_repository.hpp"

SessionRepository::SessionRepository(DbManager &dbm)
: db_manager(dbm) {}

int SessionRepository::create_token(Token token) {
  int res = 0;
  try {
    Connection *conn = db_manager.get_free_connection();

    size_t token_id = 0;
    try {
      Worker worker(*conn);
      Result result_select1 = worker.exec_prepared("insert_new_token",
        token.token, ((token.expire_date_time == "") ? "2300-01-01" : token.expire_date_time), token.user_id);
      if (!result_select1.empty()) {
        token_id = result_select1.begin()["id"].as<size_t>();
      } else {
        res = -1;
      }
      worker.commit();
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      res = -1;
    }
    if (res < 0) {
      db_manager.return_connection(conn);
      return res;
    }

    res = token_id;
    db_manager.return_connection(conn);
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    res = -1;
  }
  return res;
}

int SessionRepository::delete_token(Token token) {
  return 1;
}

int SessionRepository::check_token(const std::string &token) {
  int res = 0;
  try {
    Connection *conn = db_manager.get_free_connection();
    
    try {
      Worker worker(*conn);
      Result result_select_user = worker.exec_prepared("try_to_find_token_for_user",
        token);
      if (!result_select_user.empty()) {
        res = result_select_user.begin()["user_id"].as<size_t>();
      } else {
        res = -2;
      }
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

// User SessionRepository::get_user_by_token(Token token) {
//   User user;
//   return user;
// }
