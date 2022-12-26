#include "PartyTimeConnector.hpp"
#include "HttpConnector.hpp"
#include "LocalStorageInMemory.hpp"
#include "HttpConnectorErrorCategory.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string_view>
#include <string>
#include <memory>
#include <chrono>
using namespace std::chrono_literals;

class Timer
{
private:
	// Псевдонимы типов, чтобы упростить доступ к вложенным типам
	using clock_t = std::chrono::steady_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};


class HttpConnectorTest: public  ::testing::Test {
protected:
    void SetUp() override{
    }
    void TearDown() override{}
    HttpConnector* connector;
};

TEST_F(HttpConnectorTest, DISABLED_constructor) {
    ASSERT_EQ(1, 1);
    // HttpConnector connector("0.0.0.0", "8080");

    // auto res = connector.GET("/api/v1/events");
    // // std::cout << "catetogy = " << res.result.category().name() << std::endl;
    // // std::cout << "message = " << res.result.message() << std::endl;
    // // std::cout << res.response->response_body << std::endl;
    // Address new_addr("Ufa", 155, 233);
    // Event new_event("просто туса", "12:12:2022", 0, new_addr, "туса в Уфе", 100, 0);
    // res = connector.POST("/api/v1/events/create", new_event.toJSON());
    // std::cout << res.response->response_body << std::endl;
    // if (res.response) {
    //     std::cout << "has value" << res.response.has_value() << std::endl;
    //     std::cout << res.response->response_body << std::endl;
    //     std::cout << res.response->status.str << std::endl;
    //     for (auto&[h, v] : res.response->headers) {
    //         std::cout << "header " << h << " value " << v << std::endl;
    //     }
    // }
    // User us(0, "Name", "pwrd", "ema@mail.ru", "12:12:2022", "no desc");

    // std::cout << us.toJSON() << std::endl;
}



class LocalStorageInMemoryTest: public  ::testing::Test {
protected:
    void SetUp() override{

    }
    void TearDown() override{}
    LocalStorageInMemory* storage;
};


TEST_F(LocalStorageInMemoryTest, DISABLED_constructor) {
    ASSERT_EQ(1, 1);
}


class PartyTimeConnectorTest: public  ::testing::Test {
protected:
    void SetUp() override{
        party = PartyTimeConnector::default_implementation("0.0.0.0", "8081");
    }
    void TearDown() override{}
    std::shared_ptr<PartyTimeConnector> party;
    error_code ec;
};


TEST_F(PartyTimeConnectorTest, DISABLED_gettingEvents) {

    // auto resultat = party->events->events();
    // if (resultat.body.has_value()) {
    //     auto events = *resultat.body;
    //     for (auto & ev: events) {
    //         std::cout << "название: " << ev.title << "\t";
    //         std::cout << "описание: " << ev.description << "\t";
    //         std::cout << "дата: " << ev.date_time << "\t";
    //         // std::cout << "количество посетителей: " << *ev.max_visitors << "\t";
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // } else {
    //     std::cout << resultat.result.what() << std::endl;
    // }
}

TEST_F(PartyTimeConnectorTest, DISABLED_asyncGettingEvents) {
    auto future = party->events->events_async();
    Timer t;
    std::future_status status;
    do {
        switch(status = future.wait_for(1ms); status) {
            case std::future_status::deferred: std::cout << "deferred\n"; break;
            case std::future_status::timeout: std::cout << "timeout\n"; break;
            case std::future_status::ready: std::cout << "ready!\n"; break;
        }
    } while (status != std::future_status::ready);
    std::cout << "waited " << t.elapsed() << " seconds" << std::endl;
    auto events = future.get();
    if (events.body.has_value()) {
        for (auto& event: *events.body) {
            std::cout << "id = " << event.id << std::endl;
        }
    }
    // auto resultat = party->events->events();
    // if (resultat.body.has_value()) {
    //     auto events = *resultat.body;
    //     for (auto & ev: events) {
    //         std::cout << "название: " << ev.title << "\t";
    //         std::cout << "описание: " << ev.description << "\t";
    //         std::cout << "дата: " << ev.date_time << "\t";
    //         // std::cout << "количество посетителей: " << *ev.max_visitors << "\t";
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // } else {
    //     std::cout << resultat.result.what() << std::endl;
    // }
}

TEST_F(PartyTimeConnectorTest, creatingEvent) {

    Event event("New monday", "2022-12-12", 0, Address("Moscos", 0), "no description", 200, 1);
    // Event event;
    // event.title = "New year party";
    // event.date_time =  "2022-12-12";
    // event.description = "no desc";
    // event.address = Address("Moscow", 0);
    // std::cout << event.toJSON(ec) << std::endl;
    auto resultat = party->events->create_event(event);
    if (resultat.body) {
        std::cout << "id " << resultat.body->id << std::endl;
    } else {
        std::cout << resultat.result.message() << std::endl;
        std::cout << "failed ? " << resultat.result.failed() << std::endl;
    }
}

TEST_F(PartyTimeConnectorTest, DISABLED_asyncCreatingEvent) {

    Event event("New monday", "2022-12-12", 0, Address("Moscow", 0), "no description", 200, 1);
    // Event event;
    // event.title = "New year party";
    // event.date_time =  "2022-12-12";
    // event.description = "no desc";
    // event.address = Address("Moscow", 0);
    std::cout << event.toJSON(ec) << std::endl;
    auto resultat = party->events->create_event_async(event);
    std::future_status status;
    do {
        switch(status = resultat.wait_for(1ms); status) {
            case std::future_status::deferred: std::cout << "deferred\n"; break;
            case std::future_status::timeout: std::cout << "timeout\n"; break;
            case std::future_status::ready: std::cout << "ready!\n"; break;
        }
    } while (status != std::future_status::ready);
    auto res = resultat.get();
    std::cout << res.body->toJSON() << std::endl;
}


class HttpConnectorErrorCategoryTest: public  ::testing::Test {
protected:
    void SetUp() override{
    }
    void TearDown() override{}
};

TEST_F(HttpConnectorErrorCategoryTest, DISABLED_constructor) {
    ASSERT_EQ(1, 1);

}
