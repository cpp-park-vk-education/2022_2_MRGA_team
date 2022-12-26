#include "event_repository.hpp"
#include "user_repository.hpp"

EventRepository::EventRepository(DbManager &dbm): db_manager(dbm) {}

int EventRepository::create_event(Event event) {
  int res = 0;
  try {
    Connection *conn = db_manager.get_free_connection();

    std::string address_id = "";
    try {
      Worker worker(*conn);
      Result result_select1 = worker.exec_prepared("insert_address_if_need",
        event.address.address, event.address.longitude, event.address.latitude);
      if (!result_select1.empty()) {
        address_id = result_select1.begin()["id"].as<std::string>();
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

    size_t event_id = 0;
    try {
      Worker worker(*conn);
      Result result = worker.exec_prepared("insert_event", event.title,
        event.description, event.date_time, event.max_visitors,
        event.user_id, address_id);

      if (result.empty()) {
        res = -1;
      } else {
        event_id = result.begin()["id"].as<size_t>();
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
    res = event_id;
    db_manager.return_connection(conn);
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    res = -1;
  }
  return res;
}

std::vector<Event> EventRepository::get_events() {
  std::vector<Event> events;
  try {
    Connection *conn = db_manager.get_free_connection();

    try {
      Worker worker(*conn);
      Result result = worker.exec_prepared("select_events");
      if (!result.empty()) {
        for (auto row : result) {
          Address address(row["address"].as<std::string>(), row["longitude"].as<double>(),
          row["latitude"].as<double>(), row["address_id"].as<size_t>());

          std::set<unsigned int> some_users;
          auto arr = row["users"].as_array();
          std::pair<pqxx::array_parser::juncture, std::string> elem;
          do {
            elem = arr.get_next();
            if (elem.first == pqxx::array_parser::juncture::string_value) {
              some_users.insert(std::stoul(elem.second));
            }
          } while (elem.first != pqxx::array_parser::juncture::done);

          std::string some_overview = row["description"].as<std::string>();

          Event event(row["title"].as<std::string>(), row["date_time"].as<std::string>(),
            row["user_id"].as<size_t>(), address, ((some_overview == "null") ? "" : some_overview),
            row["max_visitors"].as<size_t>(), some_users.size(), row["events_id"].as<size_t>());
          events.push_back(event);
        }
      }

      db_manager.return_connection(conn);
    } catch (const std::exception &e) {
      db_manager.return_connection(conn);
      std::cout << e.what() << std::endl;
    }
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }
  return events;
}

int EventRepository::update_event_data(Event event) {
  return 1;
}

int EventRepository::delete_event(size_t event_id) {
  return 1;
}

int EventRepository::existence_event(size_t event_id) {
  return 1;
}

Event EventRepository::get_event_data(size_t event_id) {
  Event event;
  return event;
}

std::vector<Event> EventRepository::get_visited_events_by_user(
  size_t user_id) {
  return {};
}
std::vector<Event> EventRepository::get_organized_events_by_user(
  size_t user_id) {
  return {};
}

std::vector<User> EventRepository::get_visitors_by_event(size_t event_id) {
  return {};
}
