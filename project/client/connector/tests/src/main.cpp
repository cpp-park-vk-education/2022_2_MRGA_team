#include "connector.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Init_Test, post) {
    EXPECT_EQ(test_func(1, 4), 5);
    EXPECT_FALSE(1 == 0);
    int* i = new int[50];
    i[0] = 5;
    std::cout << i[0] << std::endl;
}