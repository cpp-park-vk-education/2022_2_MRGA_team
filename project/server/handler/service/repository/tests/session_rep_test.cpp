#include <gtest/gtest.h>
#include <iostream>

#include "session_repository.hpp"

class SessionRepTest : public ::testing::Test {
 protected:
    void SetUp() override {
        token = {
            .token = "DFGTFVGG",
            .expire_date_time = "2022-11-11 11:11:11",
            .user_id = 3526
        };
    }

    void TearDown() override {}

    DbManager db_manager;
    Token token;
};

TEST_F(SessionRepTest, CreateToken) {
    SessionRepository session_rep(db_manager);
    EXPECT_NO_THROW(session_rep.create_token(token));
}

TEST_F(SessionRepTest, DeleteToken) {
    SessionRepository session_rep(db_manager);
    EXPECT_NO_THROW(session_rep.delete_token(token));
}

TEST_F(SessionRepTest, CheckToken) {
    SessionRepository session_rep(db_manager);
    EXPECT_NO_THROW(session_rep.check_token("CJJFJDKDK"));
}

TEST_F(SessionRepTest, GetUserByToken) {
    SessionRepository session_rep(db_manager);
    EXPECT_NO_THROW(User user = session_rep.get_user_by_token(token));
}
