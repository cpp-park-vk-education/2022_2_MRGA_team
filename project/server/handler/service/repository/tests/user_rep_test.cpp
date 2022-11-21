#include <gtest/gtest.h>
#include <iostream>

#include "user_repository.hpp"


class UserConnTest : public ::testing::Test {
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

    UserRepository user_rep;
    User user;
};

TEST_F(UserConnTest, GetUserData) {
    EXPECT_NO_THROW(User user_data = user_rep.get_user_data(1232));
}


TEST_F(UserConnTest, UpdateUserData) {
    EXPECT_NO_THROW(user_rep.update_user_data(user));
}

TEST_F(UserConnTest, AddVisitor) {
    EXPECT_NO_THROW(user_rep.add_visitor(1234, 235213));
}

TEST_F(UserConnTest, DeleteVisitor) {
    EXPECT_NO_THROW(user_rep.delete_visitor(1234, 235214));
}
