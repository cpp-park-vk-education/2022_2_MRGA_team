#include <gtest/gtest.h>
#include <iostream>

#include "authorization_repository.hpp"

class AuthRepTest : public ::testing::Test {
 protected:
    void SetUp() override {}

    void TearDown() override {}

    DbManager db_manager;
};


TEST_F(AuthRepTest, CreateUser) {
    User user("jumpy", "1234", "jump@mail.ru", "2003-12-01", "Im a boy");
    AuthorizationRepository auth_rep(db_manager);
    EXPECT_NO_THROW(auth_rep.create_user(user));
}

TEST_F(AuthRepTest, ExistenceNickname) {
    AuthorizationRepository auth_rep(db_manager);
    EXPECT_TRUE(auth_rep.existence_nickname("anna_kitty"));
}

TEST_F(AuthRepTest, ExistenceEmail) {
    AuthorizationRepository auth_rep(db_manager);
    EXPECT_TRUE(auth_rep.existence_email("anna_kitty"));
}

TEST_F(AuthRepTest, CheckPassword) {
    AuthorizationRepository auth_rep(db_manager);
    EXPECT_TRUE(auth_rep.check_password(1234, "2234"));
}
