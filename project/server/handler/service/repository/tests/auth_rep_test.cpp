#include <gtest/gtest.h>
#include <iostream>

#include "authorization_repository.hpp"

class AuthConnTest : public ::testing::Test {
 protected:
    void SetUp() override {
        user = {
            .nickname = "jumpy",
            .password = "1234",
            .email = "jump@mail.ru",
            .birth_date = "2003-12-01",
            .description = "Im a boy"
        };
    }

    void TearDown() override {}

    DbManager db_manager;
    User user;
};


TEST_F(AuthConnTest, CreateUser) {
    AuthorizationRepository auth_rep(db_manager);
    EXPECT_NO_THROW(User user_data = auth_rep.create_user(user));
}

TEST_F(AuthConnTest, ExistenceNickname) {
    AuthorizationRepository auth_rep(db_manager);
    EXPECT_TRUE(auth_rep.existence_nickname("anna_kitty"));
}

TEST_F(AuthConnTest, ExistenceEmail) {
    AuthorizationRepository auth_rep(db_manager);
    EXPECT_TRUE(auth_rep.existence_email("anna_kitty"));
}

TEST_F(AuthConnTest, CheckPassword) {
    AuthorizationRepository auth_rep(db_manager);
    EXPECT_TRUE(auth_rep.check_password(1234, "2234"));
}
