#pragma once

#include <cstddef>
#include <string>

#include "objects.hpp"

class IEventConnector {
public:
  virtual Event create_event(Event event) = 0;

  virtual void update_title(size_t event_id, std::string new_title) = 0;
  virtual void update_description(size_t event_id, std::string new_description) = 0;
  virtual void update_date_time(size_t event_id, std::string new_date_time) = 0;
  virtual void update_max_visitors(size_t event_id, size_t new_max_visitors) = 0;
  virtual void update_address(size_t event_id, std::string new_address) = 0;

  virtual void add_visitor(size_t event_id, size_t profile_id) = 0;

  virtual void delete_visitor(size_t event_id, size_t profile_id) = 0;
  virtual void delete_event(size_t event_id) = 0;

  virtual Event get_event_data(size_t event_id) = 0;

  virtual std::vector<Event> get_visited_events_by_profile(size_t profile_id) = 0;
  virtual std::vector<Event> get_organized_events_by_profile(size_t profile_id) = 0;

  virtual std::vector<Profile> get_visitors_by_event(size_t event_id) = 0;
};
