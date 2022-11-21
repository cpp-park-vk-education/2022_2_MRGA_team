#include <gtest/gtest.h>
#include <iostream>

#include "authorization_repository.hpp"

class AuthConnTest : public ::testing::Test {
 protected:
    void SetUp() override {
        user = {
            .email = "jump@mail.ru",
            .birth_date = "2003-12-01",
            .description = "Im a boy",
            .nickname = "jumpy",
            .password = "1234"
        };
    }

    void TearDown() override {}

    AuthorizationRepository auth_rep;
    User user;
};


TEST_F(AuthConnTest, CreateUser) { 
    EXPECT_NO_THROW(User user_data = auth_rep.create_user(user));
}

TEST_F(AuthConnTest, ExistenceNickname) { 
    EXPECT_TRUE(auth_rep.existence_nickname("anna_kitty"));
}

TEST_F(AuthConnTest, CheckPassword) {
    EXPECT_TRUE(auth_rep.check_password(1234, "2234"));
}
