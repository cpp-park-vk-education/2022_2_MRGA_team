#include <gtest/gtest.h>
#include <iostream>

#include "utils.hpp"

TEST(Swap, HandlesPositiveInput) { 
    EXPECT_EQ(my_func(), "hello world");
}