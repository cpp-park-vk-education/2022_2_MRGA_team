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

TEST_F(DbManagerRepTest, ReturnConnection) {
    Connection c("dbname = mashadb user = mashapg password = mashapg \
      hostaddr = 127.0.0.1 port = 5432");
    
    // EXPECT_NO_THROW(db_manager.return_connection(c));

}
