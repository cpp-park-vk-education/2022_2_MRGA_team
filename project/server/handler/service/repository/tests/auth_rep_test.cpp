#include <gtest/gtest.h>
#include <iostream>

#include "authorization_repository.hpp"

class AuthRepTest : public ::testing::Test {
 protected:
    void SetUp() override {
        EXPECT_EQ(db_manager.count_connections(), db_manager.MAX_SIZE);
    }

    void TearDown() override {
        EXPECT_EQ(db_manager.count_connections(), db_manager.MAX_SIZE);
    }

    DbManager db_manager;
};


TEST_F(AuthRepTest, CreateUser) {
    AuthorizationRepository auth_rep(db_manager);
    // User user("jumpy2.0", "1234", "jumpy2.0@mail.ru");
    // EXPECT_TRUE(auth_rep.create_user(user) > 0);

    User user1("admin", "qwerty", "admin@admin.ru", "", "Im a boy");
    EXPECT_TRUE(auth_rep.create_user(user1) < 0);
}

TEST_F(AuthRepTest, ExistenceUser) {
    AuthorizationRepository auth_rep(db_manager); // Надо еще проверить что полностью существует, что пароли не сходятся

    User user("jumpy3.0", "1234", ""); // Несуществующий
    EXPECT_EQ(auth_rep.existence_user(user), -3);

    User user1("admin", "1234", ""); // Не совпадает пароль
    EXPECT_EQ(auth_rep.existence_user(user1), -2);

    User user2("admin", "qwerty", ""); // Все подошло
    EXPECT_EQ(auth_rep.existence_user(user2), 0);

    // User user3("admin2.0 OR id = 0", "qwerty", "admin@admin.ru"); // SQL-инъекция :Ъ
    // EXPECT_EQ(auth_rep.existence_user(user3), -3);
}
