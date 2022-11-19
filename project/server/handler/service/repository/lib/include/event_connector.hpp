#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "ievent_connector.hpp"

class EventConnector : public IEventConnector {
  Event create_event(Event event);

  void update_title(size_t event_id,
                    std::string new_title);
  void update_description(size_t event_id,
                          std::string new_description);
  void update_date_time(size_t event_id,
                        std::string new_date_time);
  void update_max_visitors(size_t event_id,
                           size_t new_max_visitors);
  void update_address(size_t event_id,
                      std::string new_address);

  void add_visitor(size_t event_id, size_t profile_id);

  void delete_visitor(size_t event_id, size_t profile_id);
  void delete_event(size_t event_id);

  Event get_event_data(size_t event_id);

  std::vector<Event> get_visited_events_by_profile(size_t profile_id);
  std::vector<Event> get_organized_events_by_profile(size_t profile_id);

  std::vector<Profile> get_visitors_by_event(size_t event_id);
};
