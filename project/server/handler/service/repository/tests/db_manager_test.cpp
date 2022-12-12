#include <gtest/gtest.h>
#include <iostream>

#include "db_manager.hpp"

class DbManagerRepTest : public ::testing::Test {
 protected:
    void SetUp() override {}

    void TearDown() override {}

    DbManager db_manager;
};


TEST_F(DbManagerRepTest, GetFreeAndReturnConnection) {
    Connection *conn = db_manager.get_free_connection();
    EXPECT_EQ(db_manager.count_connections(), 9);

    int res = db_manager.return_connection(conn);
    EXPECT_EQ(res, 1);
    EXPECT_EQ(db_manager.count_connections(), 10);
}
