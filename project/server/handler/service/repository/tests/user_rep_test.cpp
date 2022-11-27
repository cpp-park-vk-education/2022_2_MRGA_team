#include <gtest/gtest.h>
#include <iostream>

#include "user_repository.hpp"

class UserRepTest : public ::testing::Test {
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

TEST_F(UserRepTest, GetUserData) {
    UserRepository user_rep(db_manager);
    EXPECT_NO_THROW(User user_data = user_rep.get_user_data(1232));
}


TEST_F(UserRepTest, UpdateUserData) {
    UserRepository user_rep(db_manager);
    EXPECT_NO_THROW(user_rep.update_user_data(user));
}

TEST_F(UserRepTest, AddVisitor) {
    UserRepository user_rep(db_manager);
    EXPECT_NO_THROW(user_rep.add_visitor(1234, 235213));
}

TEST_F(UserRepTest, DeleteVisitor) {
    UserRepository user_rep(db_manager);
    EXPECT_NO_THROW(user_rep.delete_visitor(1234, 235214));
}
