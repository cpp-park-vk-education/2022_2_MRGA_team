#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <set>
#include <sstream>
#include <utility>
#include <vector>
#include "struct_mapping.hpp"

namespace {
    using std::string;
    using std::optional;
    using std::vector;
    using std::unordered_map;
    using key = string;
    using value = string;
}

//namespace structs {

    struct DBObject;
    struct User;
    struct Profile;
    struct Event;
    struct Address;
    struct Token;

    using ui = unsigned int;

    struct DBObject {
        ui id;
    public:
        DBObject() : id(0) {};
        explicit DBObject(ui id) : id(id) {};
        virtual std::string toJSON() = 0;
    };

    struct User : public DBObject {
        string nickname;  // UNIQUE
        string password;
        string email;  // UNIQUE
        string birth_date;  // Format: "yyyy-mm-dd"
        string description;  // ALLOW NULL

        User() = default;
        User(const std::string &nickname,
            const std::string &password,
            const std::string &email,
            const std::string &birth_date,
            const std::string &description = "")
        : nickname(nickname), password(password), email(email),
        birth_date(birth_date), description(description) {}

        explicit User(const string &json) {
            sm::reg(&User::id,          "id");
            sm::reg(&User::nickname,    "nickname");
            sm::reg(&User::password,    "password");
            sm::reg(&User::email,       "email");
            sm::reg(&User::description, "description");
            sm::reg(&User::birth_date,   "birthDate");

            std::stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        std::string toJSON() override {
            sm::reg(&User::id,          "id");
            sm::reg(&User::nickname,    "nickname");
            sm::reg(&User::password,    "password");
            sm::reg(&User::email,       "email");
            sm::reg(&User::description, "description");
            sm::reg(&User::birth_date,   "birthDate");

            std::ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Address : public DBObject {
        std::string address;  // NOT NULL
        double longitude;  // DEFAULT NULL
        double latitude;  // DEFAULT NULL
    public:
        Address() = default;
        Address(const std::string &address,
            const double &longitude = 0,
            const double &latitude = 0)
        : address(address), longitude(longitude), latitude(latitude) {}

        Address(const std::string &json) {
            sm::reg(&Address::id,        "id");
            sm::reg(&Address::address,   "address");
            sm::reg(&Address::longitude, "longitude");
            sm::reg(&Address::latitude,  "latitude");

            std::stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        std::string toJSON() override  {
            sm::reg(&Address::id,        "id");
            sm::reg(&Address::address,   "address");
            sm::reg(&Address::longitude, "longitude");
            sm::reg(&Address::latitude,  "latitude");

            std::ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Event : public DBObject {
        string title;  // NOT NULL
        string date_time;    // Format: "yyyy-mm-dd hh:mm:ss" NOT NULL
        ui user_id;  // NOT NULL
        Address address;  // NOT NULL

        string description;
        ui max_visitors;  // ALLOW NULL DEFAULT 100
        ui curr_visitors; // Annotation
    public:
        Event() = default;
        Event(const string &title,
            const string &date_time,
            const ui & user_id,
            const Address & address,
            const string &description = "",
            const ui &max_visitors = 100,
            const ui &curr_visitors = 0)
        : title(title), date_time(date_time), user_id(user_id),
        address(address), description(description),
        max_visitors(max_visitors), curr_visitors(curr_visitors) {}

        explicit Event(const std::string &json) {
            sm::reg(&Event::id,          "id");
            sm::reg(&Event::description, "description");
            sm::reg(&Event::date_time,    "dateTime");
            sm::reg(&Event::max_visitors, "maxVisitors");
            sm::reg(&Event::title,       "title");

            std::ostringstream out_json_data;
            std::stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }
        std::string toJSON() override {
            sm::reg(&Event::id,          "id");
            sm::reg(&Event::description, "description");
            sm::reg(&Event::date_time,    "dateTime");
            sm::reg(&Event::max_visitors, "maxVisitors");
            //sm::reg(&Event::members,     "members");
            sm::reg(&Event::title,       "title");

            std::ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Events : DBObject {
        std::vector<Event> events;

    public:
        Events() = default;
        Events(std::vector<Event> &events) :
                events(std::move(events)) {}

        Events(const std::string &json) {

            sm::reg(&Events::events,     "events");

            sm::reg(&Event::id,          "id");
            sm::reg(&Event::description, "description");
            sm::reg(&Event::date_time,    "dateTime");
            sm::reg(&Event::max_visitors, "maxVisitors");
            //sm::reg(&Event::members,     "members");
            sm::reg(&Event::title,       "title");

            std::ostringstream out_json_data;
            std::stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        std::string toJSON() override {

            sm::reg(&Events::events,     "events");

            sm::reg(&Event::id,          "id");
            sm::reg(&Event::description, "description");
            sm::reg(&Event::date_time,    "dateTime");
            sm::reg(&Event::max_visitors, "maxVisitors");
            //sm::reg(&Event::members,     "members");
            sm::reg(&Event::title,       "title");

            std::ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Token : public DBObject {
        string token;             // UNIQUE
        string expire_date_time;  // Format: "yyyy-mm-dd hh:mm:ss"
        ui user_id;

        Token() = default;
        Token(const string &token,
            const string &expire_date_time,
            const ui
            
             &user_id)
        : token(token), expire_date_time(expire_date_time), user_id(user_id) {}

        explicit Token(const std::string &json) {
            sm::reg(&Token::id,             "id");
            sm::reg(&Token::token,          "token");
            sm::reg(&Token::expire_date_time, "expireDateTime");
            sm::reg(&Token::user_id,           "userId");
            sm::reg(&User::nickname,        "nickname");
            sm::reg(&User::password,        "password");

            std::stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        std::string toJSON() override {
            sm::reg(&Token::id,             "id");
            sm::reg(&Token::token,          "token");
            sm::reg(&Token::expire_date_time, "expireDateTime");
            sm::reg(&Token::user_id,           "userId");

            sm::reg(&User::nickname,        "nickname");
            sm::reg(&User::password,        "password");

            std::ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    enum Sort {
        ASC,
        DESC
    };
    struct QueryParams {
        std::optional<size_t> limit;
        std::optional<size_t> offset;
        optional<vector<string>> order_fields;
        optional<Sort> sort;
        optional<unordered_map<key, value>> conditions;
    };

//}


#endif  // STRUCTS_HPP
