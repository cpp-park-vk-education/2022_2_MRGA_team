#include "event_repository.hpp"

EventRepository::EventRepository(DbManager &dbm): db_manager(dbm) {}

Event EventRepository::create_event(Event event) {
  Event created_event;
  return created_event;
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
