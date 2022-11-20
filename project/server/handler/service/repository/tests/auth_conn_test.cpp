#include <gtest/gtest.h>
#include <iostream>

#include "connector.hpp"


class AuthConnTest : public ::testing::Test {
 protected:
    void SetUp() override {
        profile = {
            .email = "jump@mail.ru",
            .birth_date = "2003-12-01",
            .description = "Im a boy",
            .user = {
                .nickname = "jumpy",
                .password = "1234"
            }
        };
    }

    void TearDown() override {}

    Connector connector;
    Profile profile;
};


TEST_F(AuthConnTest, CreateProfile) { 
    EXPECT_NO_THROW(Profile profile_data = connector.auth_conn->create_profile(profile));
}

TEST_F(AuthConnTest, ExistenceNickname) { 
    EXPECT_TRUE(connector.auth_conn->existence_nickname("anna_kitty"));
}

TEST_F(AuthConnTest, ExistenceEmail) { 
    EXPECT_TRUE(connector.auth_conn->existence_email("anna_kitty@hello.ru"));
}

TEST_F(AuthConnTest, GetProfileData) {
    EXPECT_NO_THROW(Profile profile_data = connector.auth_conn->get_profile_data(1232));
}


TEST_F(AuthConnTest, UpdateNickname) {
    EXPECT_NO_THROW(connector.auth_conn->update_nickname(1234, "ninjago2.0"));
}

TEST_F(AuthConnTest, UpdateEmail) {
    EXPECT_NO_THROW(connector.auth_conn->update_email(1234, "ninjago2.0@gmail.com"));
}

TEST_F(AuthConnTest, UpdatePassword) {
    EXPECT_NO_THROW(connector.auth_conn->update_password(1234, "4321"));
}

TEST_F(AuthConnTest, UpdateDescription) {
    EXPECT_NO_THROW(connector.auth_conn->update_description(1234, "Учусь теперь в УЛК :с"));
}

TEST_F(AuthConnTest, CheckPassword) {
    EXPECT_TRUE(connector.auth_conn->check_password(1234, "2234"));
}

TEST_F(AuthConnTest, DeleteProfile) {
    EXPECT_NO_THROW(connector.auth_conn->delete_profile(1234));
}

TEST_F(AuthConnTest, CreateToken) {
    EXPECT_NO_THROW(Token token_data = connector.auth_conn->create_token(1234));
}

TEST_F(AuthConnTest, DeleteToken) {
    EXPECT_NO_THROW(connector.auth_conn->delete_token(1234));
}

TEST_F(AuthConnTest, IsActualToken) {
    EXPECT_NO_THROW(std::string expiration_date_time = connector.auth_conn->get_expiration_date_time(1234));
}
