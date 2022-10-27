#include "connector.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Init_Test, post) { EXPECT_FALSE(1 == 0);
    // int* a = new int[30];
    // std::cout << a << std::endl;

    HttpRequestConnector conn("0.0.0.0", "8080");

    std::cout << conn.get_host() << " " << conn.get_port() << std::endl;

    std::cout << conn.get_host() << " " << conn.get_port() << std::endl;

    conn.test_request();

    // conn.test_request();

}

