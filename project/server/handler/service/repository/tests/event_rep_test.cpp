#include <gtest/gtest.h>
#include <iostream>

#include "event_repository.hpp"

class EventRepTest : public ::testing::Test {
 protected:
    void SetUp() override {
        EXPECT_EQ(db_manager.count_connections(), db_manager.MAX_SIZE);
    }

    void TearDown() override {
        EXPECT_EQ(db_manager.count_connections(), db_manager.MAX_SIZE);
    }

    DbManager db_manager;
};


TEST_F(EventRepTest, CreateEvent) {
    Event event("Hally hopter", "2022-01-01", 0, Address("Кремль, Москва", 3));
    EventRepository event_rep(db_manager);
    EXPECT_TRUE(event_rep.create_event(event) > 0);
}

TEST_F(EventRepTest, GetEvents) {
    EventRepository event_rep(db_manager);
    EXPECT_NO_THROW(std::vector<Event> events(event_rep.get_events()));
}

TEST_F(EventRepTest, UpdateEventData) {
    Event event("Hally hopter", "2022-01-01 23:59:59", 0, Address("Кремль, Москва", 3), "For funny people!", 10);
    EventRepository event_rep(db_manager);
    EXPECT_NO_THROW(event_rep.update_event_data(event));
}

TEST_F(EventRepTest, DeleteEvent) {
    EventRepository event_rep(db_manager);
    EXPECT_NO_THROW(event_rep.delete_event(1234));
}

TEST_F(EventRepTest, ExistenceEvent) {
    EventRepository event_rep(db_manager);
    EXPECT_NO_THROW(event_rep.existence_event(1343));
}

TEST_F(EventRepTest, GetEventData) {
    EventRepository event_rep(db_manager);
    EXPECT_NO_THROW(Event event_data = event_rep.get_event_data(1343));
}

TEST_F(EventRepTest, GetVisitedEventsByUser) {
    EventRepository event_rep(db_manager);
    EXPECT_NO_THROW(std::vector<Event> visited_event = event_rep.get_visited_events_by_user(435674));
}

TEST_F(EventRepTest, GetOrganizedEventsByUser) {
    EventRepository event_rep(db_manager);
    EXPECT_NO_THROW(std::vector<Event> organized_event = event_rep.get_organized_events_by_user(435674));
}

TEST_F(EventRepTest, GetVisitorsByEvent) {
    EventRepository event_rep(db_manager);
    EXPECT_NO_THROW(std::vector<User> organized_event = event_rep.get_visitors_by_event(342));
}
