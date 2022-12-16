#include "connector.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string_view>
#include <string>

TEST(Init_Test, post) { EXPECT_FALSE(1 == 0);
    // int* a = new int[30];
    // std::cout << a << std::endl;

    HttpRequestConnector conn("0.0.0.0", "8080");

    std::cout << conn.get_host() << " " << conn.get_port() << std::endl;

    std::cout << conn.get_host() << " " << conn.get_port() << std::endl;

    conn.test_request();

    conn.test_request();
    std::string_view sv = "string view";
    std::cout << std::string(sv) + "tt";

}

