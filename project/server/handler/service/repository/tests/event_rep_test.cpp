#include <gtest/gtest.h>
#include <iostream>

#include "event_repository.hpp"


class EventConnTest : public ::testing::Test {
 protected:
    void SetUp() override {
        event = {
            .title = "Hally hopter",
            .description = "For funny people!",
            .date_time = "2023-01-01 00:00:00",
            .max_visitors = 10,
            .address = {
                .address = "Кремль, Москва",
                .longitude = 34.0294,
                .latitude = 3.24543
            }
        };
    }

    void TearDown() override {}

    EventRepository event_rep;
    Event event;
};


TEST_F(EventConnTest, CreateEvent) { 
    EXPECT_NO_THROW(Event event_data = event_rep.create_event(event));
}

TEST_F(EventConnTest, UpdateEventData) { 
    EXPECT_NO_THROW(event_rep.update_event_data(event));
}

TEST_F(EventConnTest, DeleteEvent) {
    EXPECT_NO_THROW(event_rep.delete_event(1234));
}

TEST_F(EventConnTest, GetEventData) {
    EXPECT_NO_THROW(Event event_data = event_rep.get_event_data(1343));
}

TEST_F(EventConnTest, GetVisitedEventsByUser) {
    EXPECT_NO_THROW(std::vector<Event> visited_event = event_rep.get_visited_events_by_user(435674));
}

TEST_F(EventConnTest, GetOrganizedEventsByUser) {
    EXPECT_NO_THROW(std::vector<Event> organized_event = event_rep.get_organized_events_by_user(435674));
}

TEST_F(EventConnTest, GetVisitorsByEvent) {
    EXPECT_NO_THROW(std::vector<User> organized_event = event_rep.get_visitors_by_event(342));
}
