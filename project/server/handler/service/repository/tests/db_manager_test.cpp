#include <gtest/gtest.h>
#include <iostream>

#include "db_manager.hpp"

class DbManagerRepTest : public ::testing::Test {
 protected:
    void SetUp() override {}

    void TearDown() override {}

    DbManager db_manager;
};


TEST_F(DbManagerRepTest, GetFreeConnection) {
    EXPECT_NO_THROW(db_manager.get_free_connection());
}
