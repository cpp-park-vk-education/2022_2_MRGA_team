#include "event_repository.hpp"

EventRepository::EventRepository(DbManager &dbm): db_manager(dbm) {}

/* title, date_time и address ВО ВХОДНОЙ СТРУКТУРЕ Event
Возврат отрицательного числа - если что-то случилось,
иначе положительный id события в бд */
int EventRepository::create_event(Event event) {
  int res = 0;
  try {
    Connection *conn = db_manager.get_free_connection();
    conn->prepare("insert_address_if_need", "INSERT INTO addresses "
        "(address_title, longitude, latitude) VALUES "
        "($1, CASE WHEN $2=0 THEN null ELSE $2 END, "
        "CASE WHEN $3=0 THEN NULL ELSE $3 END) "
        "ON CONFLICT(address_title) DO UPDATE SET "
        "longitude=EXCLUDED.longitude, latitude=EXCLUDED.latitude "
        "RETURNING id;");

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

    conn->prepare("insert_event", "INSERT INTO events "
        "(title, overview, date_time, max_visitors, user_id, address_id) VALUES "
        "($1, CASE WHEN $2='' THEN null ELSE $2 END, "
        "$3, $4, $5, $6) RETURNING id;");
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

/* Возврат пустого вектора - если что-то случилось
или нет записей, иначе непустой вектора */
std::vector<Event> EventRepository::get_events() {
  std::vector<Event> events;
  try {
    Connection *conn = db_manager.get_free_connection();
    conn->prepare("select_events", "SELECT events.id AS events_id, "
                                  "events.title AS title, "
                                  "coalesce(events.overview, '') AS description, "
                                  "events.date_time AS date_time, "
                                  "events.max_visitors AS max_visitors, "
                                  "events.user_id AS user_id, "
                                  "events.address_id AS address_id, "
                                  "addresses.address_title AS address, "
                                  "coalesce(addresses.longitude, 0) AS longitude, "
                                  "coalesce(addresses.latitude, 0) AS latitude "
                                  "FROM events INNER JOIN addresses "
                                  "ON events.address_id = addresses.id "
                                  "ORDER BY events.title;");
    try {
      Worker worker(*conn);
      Result result = worker.exec_prepared("select_events");
      if (!result.empty()) {
        for (auto row : result) {
          Address address(row["address"].as<std::string>(), row["longitude"].as<double>(),
          row["latitude"].as<double>(), row["address_id"].as<size_t>());

          std::string some_overview = row["description"].as<std::string>();
          Event event(row["title"].as<std::string>(), row["date_time"].as<std::string>(),
            row["user_id"].as<size_t>(), address, ((some_overview == "null") ? "" : some_overview),
            row["max_visitors"].as<size_t>(), 0, row["events_id"].as<size_t>());
          events.push_back(event);
        }
      }

      worker.commit();
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
