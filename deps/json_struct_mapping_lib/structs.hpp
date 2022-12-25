#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <optional>
#include <unordered_map>
#include "struct_mapping.hpp"
#include "structs_error_codes.hpp"

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
        virtual string toJSON(std::error_code& ec) {
            return "";
        }
        virtual string toJSON(std::error_code& ec) const {
            return "";
        }
    };


    struct TestStruct: public DBObject {
        string some_val = [] {
            sm::reg(&TestStruct::some_val, "someval");
            return "";}();
        string toJSON() override {
            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };
    struct User : public DBObject {
        ui id = [] {
                sm::reg(&User::id, "id");
                return 0;
            }();
        string nickname = [] {
                sm::reg(&User::nickname, "nickname", sm::NotEmpty{}, sm::Required{}, sm::NotEmpty{});
                return "";
            }();  // UNIQUE
        string password = [] {
                sm::reg(&User::password, "password");
                return "";
            }();
        string email = [] {
                sm::reg(&User::email, "email", sm::Required{}, sm::NotEmpty{});
                return "";
            }();  // UNIQUE
        string birth_date = [] {
                sm::reg(&User::birth_date, "birth_date");
                return "";
            }();  // Format: "yyyy-mm-dd"
        string description = [] {
                sm::reg(&User::description, "description");
                return "";
            }();  // ALLOW NULL
        static User fromJSON(const string &json, std::error_code& ec) {
            stringstream ss(json);
            User ev;
            try {
                sm::map_json_to_struct(ev, ss);
            } catch (sm::StructMappingException& ex) {
                std::cerr << ex.what() << std::endl;
                ec.assign(int(structs_error_codes::parsing_error), structs_error_category());
                return ev;
            }
            ec.assign(int(structs_error_codes::success), structs_error_category());
            return ev;
        }
        User() = default;
        User(const string &nickname,
            const string &password,
            const string &email,
            const string &birth_date = "2300-12-31",
            const string &description = "",
            const ui &id = 0)
        : id(id), nickname(nickname), password(password), email(email),
        birth_date(birth_date), description(description) {}

        explicit User(const string &json) {
            stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        string toJSON() override {
            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
        string toJSON(std::error_code& ec) override {
            if (this->nickname.empty()) {
                ec.assign(int(structs_error_codes::empty_nickname), structs_error_category());
                return "";
            }
            ec.assign(int(structs_error_codes::success), structs_error_category());
            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
        string toJSON(std::error_code& ec) const override {
            auto user = *this;
            return user.toJSON(ec);
        }
    };

    struct Address : public DBObject {
        ui id = []{
            return 0;
            sm::reg(&Address::id, "id");
        }();
        string address = []{
            sm::reg(&Address::address, "address", sm::NotEmpty{}, sm::Required{});
            return "";
        }();  // NOT NULL
        double longitude = []{
            sm::reg(&Address::longitude, "longitude");
            return 0;
        }();  // DEFAULT NULL
        double latitude = []{
            sm::reg(&Address::latitude, "latitude");
            return 0;
        }();  // DEFAULT NULL
    public:
        Address() = default;
        Address(const string &address,
            const double &longitude = 0,
            const double &latitude = 0,
            const ui &id = 0)
        : id(id), address(address), longitude(longitude), latitude(latitude) {}

        Address(const string &json) {
            stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        string toJSON() override  {
            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Event : public DBObject {
        string title = [] {
            sm::reg(&Event::title, "title", sm::NotEmpty{}, sm::Required{});
            return "";
        }();  // NOT NULL
        string date_time = [] {
            sm::reg(&Event::date_time, "dateTime", sm::NotEmpty{}, sm::Required{});
            return "";
        }();    // Format: "yyyy-mm-dd hh:mm:ss" NOT NULL
        ui user_id = [] {
            sm::reg(&Event::user_id, "userId");
            return 0;
        } ();  // NOT NULL
        Address address = []{
            sm::reg(&Event::address, "address");
            return Address{};
        }();  // NOT NULL

        string description = [] {
            sm::reg(&Event::description, "description");
            return "";
        }();
        optional<ui> max_visitors = [] {
            sm::reg(&Event::max_visitors, "maxVisitors");
            return std::nullopt;
        }(); // ALLOW NULL DEFAULT 100
        ui curr_visitors = [] {
            sm::reg(&Event::curr_visitors, "currVisitors");
            return 0;
        }(); // Annotation
        ui id = []{
            sm::reg(&Event::id, "id");
            return 0;
        }();
    public:
        static Event fromJSON(const string &json, std::error_code& ec) {
            stringstream ss(json);
            Event ev;
            try {
                sm::map_json_to_struct(ev, ss);
            } catch (sm::StructMappingException& ex) {
                std::cerr << ex.what() << std::endl;
                ec.assign(int(structs_error_codes::parsing_error), structs_error_category());
                return ev;
            }
            ec.assign(int(structs_error_codes::success), structs_error_category());
            return ev;
        }
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
            stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }
        string toJSON(std::error_code& ec) override {
            if (this->title.empty()) {
                ec.assign(int(structs_error_codes::empty_title), structs_error_category());
                return "";
            }
            if (this->date_time.empty()) {
                ec.assign(int(structs_error_codes::empty_date), structs_error_category());
                return "";
            }
            ec.assign(int(structs_error_codes::success), structs_error_category());
            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();

        }
        string toJSON(std::error_code& ec) const override {
            auto event = *this;
            return event.toJSON(ec);
        }
        string toJSON() override {
            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };
    struct Events : DBObject {

    vector<Event> events = []()->vector<Event>{
        sm::reg(&Events::events,     "events");
        return {};
    }();

    public:
        Events() = default;
        Events(vector<Event> &events) :
                events(move(events)) {}

        Events(const string &json) {
            stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        string toJSON() override {
            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Token : public DBObject {
        ui id = []{
            sm::reg(&Token::id, "id");
            return 0;
        }();
        string token = [] {
            sm::reg(&Token::token,          "token");
            return "";
        }();             // UNIQUE
        string expire_date_time = []{
            sm::reg(&Token::expire_date_time, "expireDateTime");
            return "";
        }();  // Format: "yyyy-mm-dd hh:mm:ss"
        ui user_id = []{
            sm::reg(&Token::user_id, "userId");
            return 0;
        }();

        Token() = default;
        Token(const string &token,
            const string &expire_date_time,
            const ui &user_id,
            const ui &id = 0)
        : id(id), token(token), expire_date_time(expire_date_time), user_id(user_id) {}

        explicit Token(const string &json) {
            stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }

        string toJSON() override {
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

namespace __structs__{
    static Event __event__;
    static Events __events__;
    static Token __token__;
    static User __user__;
};

//}

#endif  // STRUCTS_HPP

