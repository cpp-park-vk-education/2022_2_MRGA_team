#include "connector.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Init_Test, post) { EXPECT_FALSE(1 == 0);
    int* a = new int[30];
    std::cout << a << std::endl;
}