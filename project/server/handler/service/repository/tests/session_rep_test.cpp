#include <gtest/gtest.h>
#include <iostream>

#include "session_repository.hpp"

class SessionRepTest : public ::testing::Test {
 protected:
    void SetUp() override {
        EXPECT_EQ(db_manager.count_connections(), db_manager.MAX_SIZE);
    }

    void TearDown() override {
        EXPECT_EQ(db_manager.count_connections(), db_manager.MAX_SIZE);
    }

    DbManager db_manager;
};

TEST_F(SessionRepTest, CreateToken) {
    Token token("DFGTFVGG", "2022-11-11 11:11:11", 0);
    SessionRepository session_rep(db_manager);
    EXPECT_NO_THROW(session_rep.create_token(token));
}

TEST_F(SessionRepTest, DeleteToken) {
    Token token("DFGTFVGG", "2022-11-11 11:11:11", 0);
    SessionRepository session_rep(db_manager);
    EXPECT_NO_THROW(session_rep.delete_token(token));
}

TEST_F(SessionRepTest, CheckToken) {
    SessionRepository session_rep(db_manager);
    EXPECT_NO_THROW(session_rep.check_token("CJJFJDKDK"));
}

TEST_F(SessionRepTest, GetUserByToken) {
    Token token("DFGTFVGG", "2022-11-11 11:11:11", 0);
    SessionRepository session_rep(db_manager);
    EXPECT_NO_THROW(User user = session_rep.get_user_by_token(token));
}
