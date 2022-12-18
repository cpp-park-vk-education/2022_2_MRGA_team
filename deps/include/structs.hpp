#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <set>
#include <sstream>
#include <utility>
#include <vector>
#include <optional>
#include "struct_mapping.hpp"

namespace {
    using std::optional;
    using std::stringstream;
    using std::ostringstream;
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
    public:
        virtual string toJSON() = 0;
    };

    struct User : public DBObject {
        ui id;
        string nickname;  // UNIQUE
        string password;
        string email;  // UNIQUE
        string birth_date;  // Format: "yyyy-mm-dd"
        string description;  // ALLOW NULL

        User() = default;
        User(const string &nickname,
            const string &password,
            const string &email,
            const string &birth_date,
            const string &description = "",
            const ui &id = 0)
        : id(id), nickname(nickname), password(password), email(email),
        birth_date(birth_date), description(description) {}

        explicit User(const string &json) {
            sm::reg(&User::nickname,    "nickname");
            sm::reg(&User::password,    "password");
            sm::reg(&User::email,       "email");
            sm::reg(&User::description, "description");
            sm::reg(&User::birth_date,   "birthDate");

            sm::reg(&User::id,          "id");

            stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        string toJSON() override {
            sm::reg(&User::nickname,    "nickname");
            sm::reg(&User::password,    "password");
            sm::reg(&User::email,       "email");
            sm::reg(&User::description, "description");
            sm::reg(&User::birth_date,   "birthDate");

            sm::reg(&User::id,          "id");

            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Address : public DBObject {
        ui id;
        string address;  // NOT NULL
        double longitude;  // DEFAULT NULL
        double latitude;  // DEFAULT NULL
    public:
        Address() = default;
        Address(const string &address,
            const double &longitude = 0,
            const double &latitude = 0,
            const ui &id = 0)
        : id(id), address(address), longitude(longitude), latitude(latitude) {}

        Address(const string &json) {
            sm::reg(&Address::address,   "address");
            sm::reg(&Address::longitude, "longitude");
            sm::reg(&Address::latitude,  "latitude");

            sm::reg(&Address::id,        "id");

            stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        string toJSON() override  {
            sm::reg(&Address::address,   "address");
            sm::reg(&Address::longitude, "longitude");
            sm::reg(&Address::latitude,  "latitude");

            sm::reg(&Address::id,        "id");

            ostringstream outJsonData;
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
        optional<ui> max_visitors;  // ALLOW NULL DEFAULT 100
        ui curr_visitors; // Annotation
        ui id;
    public:
        Event() = default;
        Event(const string &title,
            const string &date_time,
            const ui & user_id,
            const Address & address,
            const string &description = "",
            const ui &max_visitors = 100,
            const ui &curr_visitors = 0,
            const ui &id = 0)
        : id(id), title(title), date_time(date_time), user_id(user_id),
        address(address), description(description),
        max_visitors(max_visitors), curr_visitors(curr_visitors) {}

        explicit Event(const string &json) {
            sm::reg(&Event::title,       "title");
            sm::reg(&Event::date_time,    "dateTime");
            sm::reg(&Event::user_id,    "userId");
            sm::reg(&Event::description, "description");
            sm::reg(&Event::max_visitors, "maxVisitors");
            sm::reg(&Event::curr_visitors, "currVisitors");
            sm::reg(&Event::address, "address");
            sm::reg(&Event::id, "id");

            sm::reg(&Address::address,   "address");
            sm::reg(&Address::longitude, "longitude");
            sm::reg(&Address::latitude,  "latitude");
            sm::reg(&Address::id,        "id");

            stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }
        string toJSON() override {
            sm::reg(&Event::title,       "title");
            sm::reg(&Event::date_time,    "dateTime");
            sm::reg(&Event::user_id,    "userId");
            sm::reg(&Event::description, "description");
            sm::reg(&Event::max_visitors, "maxVisitors");
            sm::reg(&Event::curr_visitors, "currVisitors");
            sm::reg(&Event::address, "address");
            sm::reg(&Event::id, "id");

            sm::reg(&Address::address,   "address");
            sm::reg(&Address::longitude, "longitude");
            sm::reg(&Address::latitude,  "latitude");
            sm::reg(&Address::id,        "id");

            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Events : DBObject {

    vector<Event> events;

    public:
        Events() = default;
        Events(vector<Event> &events) :
                events(move(events)) {}

        Events(const string &json) {
            sm::reg(&Events::events,     "events");

            sm::reg(&Event::title,       "title");
            sm::reg(&Event::date_time,    "dateTime");
            sm::reg(&Event::user_id,    "userId");
            sm::reg(&Event::description, "description");
            sm::reg(&Event::max_visitors, "maxVisitors");
            sm::reg(&Event::curr_visitors, "currVisitors");
            sm::reg(&Event::address, "address");
            sm::reg(&Event::id, "id");

            sm::reg(&Address::address,   "address");
            sm::reg(&Address::longitude, "longitude");
            sm::reg(&Address::latitude,  "latitude");
            sm::reg(&Address::id,        "id");

            stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        string toJSON() override {

            sm::reg(&Events::events,     "events");

            sm::reg(&Event::title,       "title");
            sm::reg(&Event::date_time,    "dateTime");
            sm::reg(&Event::user_id,    "userId");
            sm::reg(&Event::description, "description");
            sm::reg(&Event::max_visitors, "maxVisitors");
            sm::reg(&Event::curr_visitors, "currVisitors");
            sm::reg(&Event::address, "address");
            sm::reg(&Event::id, "id");

            sm::reg(&Address::address,   "address");
            sm::reg(&Address::longitude, "longitude");
            sm::reg(&Address::latitude,  "latitude");
            sm::reg(&Address::id,        "id");

            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Token : public DBObject {
        ui id;
        string token;             // UNIQUE
        string expire_date_time;  // Format: "yyyy-mm-dd hh:mm:ss"
        ui user_id;

        Token() = default;
        Token(const string &token,
            const string &expire_date_time,
            const ui &user_id,
            const ui &id = 0)
        : id(id), token(token), expire_date_time(expire_date_time), user_id(user_id) {}

        explicit Token(const string &json) {
            sm::reg(&Token::id,             "id");
            sm::reg(&Token::token,          "token");
            sm::reg(&Token::expire_date_time, "expireDateTime");
            sm::reg(&Token::user_id,           "userId");
            sm::reg(&User::nickname,        "nickname");
            sm::reg(&User::password,        "password");

            stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        string toJSON() override {
            sm::reg(&Token::id,             "id");
            sm::reg(&Token::token,          "token");
            sm::reg(&Token::expire_date_time, "expireDateTime");
            sm::reg(&Token::user_id,           "userId");

            sm::reg(&User::nickname,        "nickname");
            sm::reg(&User::password,        "password");

            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    enum Sort {
        ASC,
        DESC
    };
    struct QueryParams {
        optional<size_t> limit;
        optional<size_t> offset;
        optional<vector<string>> order_fields;
        optional<Sort> sort;
        optional<unordered_map<key, value>> conditions;
    };

//}

#endif  // STRUCTS_HPP
