#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "ievent_repository.hpp"

class EventRepository : public IEventRepository {
 public:
  Event create_event(Event event);

  void update_event_data(Event event) ;

  void delete_event(size_t event_id);

  Event get_event_data(size_t event_id);

  std::vector<Event> get_visited_events_by_user(size_t user_id);
  std::vector<Event> get_organized_events_by_user(size_t user_id);

  std::vector<User> get_visitors_by_event(size_t event_id);
};
