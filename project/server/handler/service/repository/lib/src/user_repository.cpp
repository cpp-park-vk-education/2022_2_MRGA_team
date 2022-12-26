#include "user_repository.hpp"

UserRepository::UserRepository(DbManager &dbm) : db_manager(dbm) {}

int UserRepository::existence_user_by_id(size_t user_id) {
  int res = 0;
  try {
    Connection *conn = db_manager.get_free_connection();
    
    try {
      Worker worker(*conn);
      Result result_select_user = worker.exec_prepared("try_to_find_user_by_id", user_id);
      if (!result_select_user.empty()) {
        size_t got_res = result_select_user.begin()["result"].as<size_t>();
        if (got_res == 200) {
          res = 1;
        } else {
          res = -1;
        }
      } else {
        res = 0;
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

User UserRepository::get_user_data(size_t user_id) {
  int res = 0;
  try {
    Connection *conn = db_manager.get_free_connection();

    try {
      Worker worker(*conn);
      Result result_select_user_data = worker.exec_prepared("get_user_data_by_id", user_id);
      if (!result_select_user_data.empty()) {
        std::string nickname = result_select_user_data.begin()["nickname"].as<std::string>();
        std::string password = result_select_user_data.begin()["passcode"].as<std::string>();
        std::string email = result_select_user_data.begin()["email"].as<std::string>();

        std::string birth_date = result_select_user_data.begin()["birth_date"].as<std::string>();
        birth_date = ((birth_date == "1300-11-13") ? "" : birth_date);
        std::string description = result_select_user_data.begin()["overview"].as<std::string>();
        User user(nickname, password, email, birth_date, description, user_id);

        std::set<unsigned int> some_events;
        auto arr = result_select_user_data.begin()["events"].as_array();
        std::pair<pqxx::array_parser::juncture, string> elem;
        do {
          elem = arr.get_next();
          if (elem.first == pqxx::array_parser::juncture::string_value) {
            some_events.insert(std::stoul(elem.second));
          }
        } while (elem.first != pqxx::array_parser::juncture::done);
        user.events = some_events;
        db_manager.return_connection(conn);
        return user;
      } else {
        res = -1;
      }
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      res = -1;
    }

    if (res < 0) {
      db_manager.return_connection(conn);
      User user;
      return user;
    }
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    res = -1;
  }
  User user;
  return user;
}

int UserRepository::update_user_data(User user) {
  return 1;
}

int UserRepository::add_visitor(size_t event_id, size_t user_id) {
  return 1;
}

int UserRepository::delete_visitor(size_t event_id, size_t user_id) {
  return 1;
}
