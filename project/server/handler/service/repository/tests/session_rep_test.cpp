#include <gtest/gtest.h>
#include <iostream>

#include "session_repository.hpp"

class SessionRepTest : public ::testing::Test {
 protected:
    void SetUp() override {
        token = {
            .id = 45,
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
    EXPECT_NO_THROW(Token token_data = session_rep.create_token(1234));
}

TEST_F(SessionRepTest, DeleteToken) {
    SessionRepository session_rep(db_manager);
    EXPECT_NO_THROW(session_rep.delete_token(token));
}

TEST_F(SessionRepTest, GetTokens) {
    SessionRepository session_rep(db_manager);
    EXPECT_NO_THROW(std::vector<Token> tokens = session_rep.get_tokens(1234));
}
