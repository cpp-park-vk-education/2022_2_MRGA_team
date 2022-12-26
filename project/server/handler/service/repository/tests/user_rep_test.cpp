#include <gtest/gtest.h>
#include <iostream>

#include "user_repository.hpp"
#include "authorization_repository.hpp"

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
    User user_data = user_rep.get_user_data(1232);
    EXPECT_TRUE(user_data.nickname == "");

    User user_data1 = user_rep.get_user_data(0);
    EXPECT_TRUE(user_data1.nickname == "admin");
    EXPECT_TRUE(user_data1.id == 0);
    EXPECT_TRUE(user_data1.password == "qwerty");
    EXPECT_TRUE(user_data1.email == "admin@admin.ru");
    EXPECT_TRUE(user_data1.birth_date == "1970-01-01");
    EXPECT_TRUE(user_data1.description == "this user is admin");

    // User need_to_add_user("jumpy2.0", "1234", "jumpy2.0@mail.ru");
    // AuthorizationRepository auth_rep(db_manager);
    // auth_rep.create_user(need_to_add_user);
    // User user_data2 = user_rep.get_user_data(2);
    // EXPECT_EQ(user_data2.nickname, "jumpy2.0");
    // EXPECT_EQ(user_data2.id, 2);
    // EXPECT_EQ(user_data2.password, "1234");
    // EXPECT_TRUE(user_data2.email == "jumpy2.0@mail.ru");
    // EXPECT_EQ(user_data2.birth_date, "");
    // EXPECT_EQ(user_data2.description, "");
}


TEST_F(UserRepTest, UpdateUserData) {
    User user("jumpy", "1234", "jump@mail.ru", "2003-12-01", "Im a boy");
    UserRepository user_rep(db_manager);
    EXPECT_NO_THROW(user_rep.update_user_data(user));
}

TEST_F(UserRepTest, AddVisitor) {
    UserRepository user_rep(db_manager);
    EXPECT_EQ(user_rep.add_visitor(1234, 235213), 1); // Не должна вызываться ошибка
    EXPECT_EQ(user_rep.add_visitor(1, 0), 1);
    EXPECT_EQ(user_rep.add_visitor(1, 0), 1);
    User got_user = user_rep.get_user_data(0);
    EXPECT_EQ(got_user.events.size(), 1);
    EXPECT_EQ(*got_user.events.begin(), 1);
}

TEST_F(UserRepTest, DeleteVisitor) {
    UserRepository user_rep(db_manager);
    EXPECT_EQ(user_rep.delete_visitor(1234, 235213), 1); // Не должна вызываться ошибка
    EXPECT_EQ(user_rep.delete_visitor(1, 0), 1);
    EXPECT_EQ(user_rep.delete_visitor(1, 0), 1);
    User got_user = user_rep.get_user_data(0);
    EXPECT_EQ(got_user.events.size(), 0);
    EXPECT_EQ(*got_user.events.begin(), 1);
}
