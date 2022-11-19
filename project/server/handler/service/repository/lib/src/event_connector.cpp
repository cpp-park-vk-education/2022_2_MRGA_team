#include "event_connector.hpp"

Event EventConnector::create_event(Event event) {
  Event created_event;
  return created_event;
}

void EventConnector::update_title(size_t event_id,
                                  std::string new_title) {}
void EventConnector::update_description(size_t event_id,
                                        std::string new_description) {}
void EventConnector::update_date_time(size_t event_id,
                                      std::string new_date_time) {}
void EventConnector::update_max_visitors(size_t event_id,
                                         size_t new_max_visitors) {}
void EventConnector::update_address(size_t event_id,
                                    std::string new_address) {}

void EventConnector::add_visitor(size_t event_id, size_t profile_id) {}

void EventConnector::delete_visitor(size_t event_id, size_t profile_id) {}
void EventConnector::delete_event(size_t event_id) {}

Event EventConnector::get_event_data(size_t event_id) {
  Event event;
  return event;
}

std::vector<Event> EventConnector::get_visited_events_by_profile(
  size_t profile_id) {
  return {};
}
std::vector<Event> EventConnector::get_organized_events_by_profile(
  size_t profile_id) {
  return {};
}

std::vector<Profile> EventConnector::get_visitors_by_event(size_t patry_id) {
  return {};
}
