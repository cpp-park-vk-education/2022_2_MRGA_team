#include "PartyTimeConnector.hpp"
#include "HttpConnector.hpp"
#include "LocalStorageInMemory.hpp"
#include "HttpConnectorErrorCategory.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string_view>
#include <string>


class HttpConnectorTest: public  ::testing::Test {
protected:
    void SetUp() override{
    }
    void TearDown() override{}
    HttpConnector* connector;
};

TEST_F(HttpConnectorTest, constructor) {
    ASSERT_EQ(1, 1);
}



class LocalStorageInMemoryTest: public  ::testing::Test {
protected:
    void SetUp() override{

    }
    void TearDown() override{}
    LocalStorageInMemory* storage;
};


TEST_F(LocalStorageInMemoryTest, constructor) {
    ASSERT_EQ(1, 1);
}


class PartyTimeConnectorTest: public  ::testing::Test {
protected:
    void SetUp() override{}
    void TearDown() override{}
    PartyTimeConnector* party;
};


TEST_F(PartyTimeConnectorTest, constructor) {
    ASSERT_EQ(1, 1);
}


class HttpConnectorErrorCategoryTest: public  ::testing::Test {
protected:
    void SetUp() override{
    }
    void TearDown() override{}
    HttpConnectorErrorCategory* connector;
};

TEST_F(HttpConnectorErrorCategoryTest, constructor) {
    ASSERT_EQ(1, 1);
    HttpConnector connector("contest.yandex.ru");
    auto res = connector.GET("/");
    std::cout << "has value" << res.has_value() << std::endl;
    std::cout << res->response_body << std::endl;
    std::cout << res->status.str << std::endl;
    for (auto&[h, v] : res->headers) {
        std::cout << "header " << h << " value " << v << std::endl;
    }
}