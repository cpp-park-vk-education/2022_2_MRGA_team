#include <gtest/gtest.h>
#include <iostream>

#include "connector.hpp"


class EventConnTest : public ::testing::Test {
 protected:
    void SetUp() override {
        Event kevent = {
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

    Connector connector;
    Event event;
};


TEST_F(EventConnTest, CreateEvent) { 
    EXPECT_NO_THROW(Event event_data = connector.event_conn->create_event(event));
}

TEST_F(EventConnTest, UpdateTitle) { 
    EXPECT_NO_THROW(connector.event_conn->update_title(1234, "Хэллоуин"));
}

TEST_F(EventConnTest, UpdateDescription) { 
    EXPECT_NO_THROW(connector.event_conn->update_description(1234, "И не забудьте про дресс-код"));
}

TEST_F(EventConnTest, UpdateDateTime) {
    EXPECT_NO_THROW(connector.event_conn->update_date_time(1234, "2022-11-11 11:11:11"));
}

TEST_F(EventConnTest, UpdateAddress) {
    EXPECT_NO_THROW(connector.event_conn->update_address(1234, "В деревне у бабушки"));
}

TEST_F(EventConnTest, UpdateMaxVisitors) {
    EXPECT_NO_THROW(connector.event_conn->update_max_visitors(1234, 111));
}

TEST_F(EventConnTest, AddVisitor) {
    EXPECT_NO_THROW(connector.event_conn->add_visitor(1234, 235213));
}

TEST_F(EventConnTest, DeleteVisitor) {
    EXPECT_NO_THROW(connector.event_conn->delete_visitor(1234, 235214));
}

TEST_F(EventConnTest, DeleteEvent) {
    EXPECT_NO_THROW(connector.event_conn->delete_event(1234));
}

TEST_F(EventConnTest, GetEventData) {
    EXPECT_NO_THROW(Event event_data = connector.event_conn->get_event_data(1343));
}

TEST_F(EventConnTest, GetVisitedEventsByProfile) {
    EXPECT_NO_THROW(std::vector<Event> visited_event = connector.event_conn->get_visited_events_by_profile(435674));
}

TEST_F(EventConnTest, GetOrganizedEventsByProfile) {
    EXPECT_NO_THROW(std::vector<Event> organized_event = connector.event_conn->get_organized_events_by_profile(435674));
}

TEST_F(EventConnTest, GetVisitorsByEvent) {
    EXPECT_NO_THROW(std::vector<Profile> organized_event = connector.event_conn->get_visitors_by_event(342));
}
