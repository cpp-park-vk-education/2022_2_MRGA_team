#pragma once

#include <cstddef>
#include <string>

#include "objects.hpp"

class IEventRepository {
public:
  virtual Event create_event(Event event) = 0;

  virtual void update_event_data(Event event) = 0;

  virtual void delete_event(size_t event_id) = 0;

  virtual Event get_event_data(size_t event_id) = 0;

  virtual std::vector<Event> get_visited_events_by_user(size_t user_id) = 0;
  virtual std::vector<Event> get_organized_events_by_user(size_t user_id) = 0;

  virtual std::vector<User> get_visitors_by_event(size_t event_id) = 0;
};
