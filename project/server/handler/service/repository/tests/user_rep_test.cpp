#include <gtest/gtest.h>
#include <iostream>

#include "user_repository.hpp"

class UserRepTest : public ::testing::Test {
 protected:
    void SetUp() override {
        EXPECT_EQ(db_manager.count_connections(), db_manager.MAX_SIZE);
    }

    void TearDown() override {
        EXPECT_EQ(db_manager.count_connections(), db_manager.MAX_SIZE);
    }

    DbManager db_manager;
};

TEST_F(UserRepTest, ExistenceUserById) {
    UserRepository user_rep(db_manager);
    EXPECT_EQ(user_rep.existence_user_by_id(1232), 0);
    EXPECT_EQ(user_rep.existence_user_by_id(0), 1);
}

TEST_F(UserRepTest, GetUserData) {
    UserRepository user_rep(db_manager);
    EXPECT_NO_THROW(User user_data = user_rep.get_user_data(1232));
}


TEST_F(UserRepTest, UpdateUserData) {
    User user("jumpy", "1234", "jump@mail.ru", "2003-12-01", "Im a boy");
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
