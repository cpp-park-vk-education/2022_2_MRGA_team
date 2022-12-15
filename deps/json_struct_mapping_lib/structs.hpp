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
    using std::move;
    using std::optional;
    using std::vector;
    using std::stringstream;
    using std::unordered_map;
    using key = string;
    using value = string;
    using std::ostringstream;
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
        ui _id;
    public:
        DBObject() : _id(0) {};
        explicit DBObject(ui id) : _id(id) {};
        virtual string toJSON() = 0;
    };

    struct User : public DBObject {
        string _nickname;    // UNIQUE
        string _password;
        string _email;       // UNIQUE
        string _birthDate;   // Format: "yyyy-mm-dd"
        string _description; // ALLOW NULL
    public:
        User() = default;
        User(ui id, const string &nickname, const string &password, const string &email,
            const string &birthDate, const string &description) :
                DBObject(id),
                _nickname    (move(nickname)),
                _password    (move(password)),
                _email       (move(email)),
                _birthDate   (move(birthDate)),
                _description (move(description)) {};

        explicit User(const string &json) {
            sm::reg(&User::_id,          "id");
            sm::reg(&User::_nickname,    "nickname");
            sm::reg(&User::_password,    "password");
            sm::reg(&User::_email,       "email");
            sm::reg(&User::_description, "description");
            sm::reg(&User::_birthDate,   "birthDate");

            stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }
        string toJSON() override {
            sm::reg(&User::_id,          "id");
            sm::reg(&User::_nickname,    "nickname");
            sm::reg(&User::_password,    "password");
            sm::reg(&User::_email,       "email");
            sm::reg(&User::_description, "description");
            sm::reg(&User::_birthDate,   "birthDate");

            ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Profile : public DBObject {
        User        _user;
        std::string _email;        // UNIQUE
        std::string _birthDate;    // Format: "yyyy-mm-dd"
        std::string _description;  // ALLOW NULL
    public:
        Profile() = default;
        Profile(ui id, std::string &email, const string &birthDate, User &user, const string &description = "") :
                DBObject(id),
                _user        (std::move(user)),
                _email       (std::move(email)),
                _birthDate   (std::move(birthDate)),
                _description (std::move(description)) {};

        explicit Profile(const std::string &json) {
            sm::reg(&Profile::_id,          "id");
            sm::reg(&Profile::_email,       "email");
            sm::reg(&Profile::_description, "description");
            sm::reg(&Profile::_birthDate,   "birthDate");
            sm::reg(&Profile::_user,        "user");

            sm::reg(&User::_nickname,       "nickname");
            sm::reg(&User::_password,       "password");

            std::stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }
        std::string toJSON() override {
            sm::reg(&Profile::_id,          "id");
            sm::reg(&Profile::_email,       "email");
            sm::reg(&Profile::_description, "description");
            sm::reg(&Profile::_birthDate,   "birthDate");
            sm::reg(&Profile::_user,        "user");

            sm::reg(&User::_nickname,       "nickname");
            sm::reg(&User::_password,       "password");

            std::ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Address : public DBObject {
        std::string _address;
        double      _longitude = 0;
        double      _latitude = 0;
    public:
        Address() = default;
        Address(ui id, const std::string &address, double longitude, double latitude) :
                DBObject(id),
                _address   (std::move(address)),
                _longitude (longitude),
                _latitude  (latitude) {}

        Address(const std::string &json) {
            sm::reg(&Address::_id,        "id");
            sm::reg(&Address::_address,   "address");
            sm::reg(&Address::_longitude, "longitude");
            sm::reg(&Address::_latitude,  "latitude");

            std::stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }
            std::string toJSON() override  {
            sm::reg(&Address::_id,        "id");
            sm::reg(&Address::_address,   "address");
            sm::reg(&Address::_longitude, "longitude");
            sm::reg(&Address::_latitude,  "latitude");

            std::ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Event : public DBObject {
        //std::set<ui> _members;
        std::string    _title;
        std::string    _description;
        std::string    _dateTime;         // Format: "yyyy-mm-dd hh:mm:ss"
        ui             _maxVisitors = 0;  // ALLOW NULL
        ui             _currVisitors = 0; // Annotation
        ui             _userId;
        Address        _address;
    public:
        Event() = default;
        Event(ui id,
                //std::set<ui> &members,
              const std::string    &tittle,
              const std::string    &description,
              const std::string    &dateTime,
              ui            maxVisitors,
              ui            currVisitors,
              ui            userId,
              Address       address
              ) :

                DBObject(id),
                //_members     (std::move(members)),
                _title        (std::move(tittle)),
                _description  (std::move(description)),
                _dateTime     (std::move(dateTime)),
                _maxVisitors  (maxVisitors),
                _currVisitors (currVisitors),
                _userId       (userId),
                 _address     (std::move(address))

                {};

        explicit Event(const std::string &json) {
            sm::reg(&Event::_id,          "id");
            sm::reg(&Event::_description, "description");
            sm::reg(&Event::_dateTime,    "dateTime");
            sm::reg(&Event::_maxVisitors, "maxVisitors");
            //sm::reg(&Event::_members,     "members");
            sm::reg(&Event::_title,       "title");

            std::ostringstream out_json_data;
            std::stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }
        std::string toJSON() override {
            sm::reg(&Event::_id,          "id");
            sm::reg(&Event::_description, "description");
            sm::reg(&Event::_dateTime,    "dateTime");
            sm::reg(&Event::_maxVisitors, "maxVisitors");
            //sm::reg(&Event::_members,     "members");
            sm::reg(&Event::_title,       "title");

            std::ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Events : DBObject {
        std::vector<Event> _events;

    public:
        Events() = default;
        Events(std::vector<Event> &events) :
                _events(std::move(events)) {}

        Events(const std::string &json) {

            sm::reg(&Events::_events,     "events");

            sm::reg(&Event::_id,          "id");
            sm::reg(&Event::_description, "description");
            sm::reg(&Event::_dateTime,    "dateTime");
            sm::reg(&Event::_maxVisitors, "maxVisitors");
            //sm::reg(&Event::_members,     "members");
            sm::reg(&Event::_title,       "title");

            std::ostringstream out_json_data;
            std::stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }
        std::string toJSON() override {

            sm::reg(&Events::_events,     "events");

            sm::reg(&Event::_id,          "id");
            sm::reg(&Event::_description, "description");
            sm::reg(&Event::_dateTime,    "dateTime");
            sm::reg(&Event::_maxVisitors, "maxVisitors");
            //sm::reg(&Event::_members,     "members");
            sm::reg(&Event::_title,       "title");

            std::ostringstream outJsonData;
            sm::map_struct_to_json(*(this), outJsonData);
            return outJsonData.str();
        }
    };

    struct Token : public DBObject {
        std::string _token;           // UNIQUE
        std::string _expireDateTime;  // Format: "yyyy-mm-dd hh:mm:ss"
        ui       _userId;
    public:
        Token() = default;
        Token(ui id, std::string &token, std::string &expireDateTime, ui userId) :
                DBObject(id),
                _token          (std::move(token)),
                _expireDateTime (std::move(expireDateTime)),
                _userId           (userId) {}

        explicit Token(const std::string &json) {
            sm::reg(&Token::_id,             "id");
            sm::reg(&Token::_token,          "token");
            sm::reg(&Token::_expireDateTime, "expireDateTime");
            sm::reg(&Token::_userId,           "userId");

            sm::reg(&User::_nickname,        "nickname");
            sm::reg(&User::_password,        "password");

            std::stringstream ss(json);
            sm::map_json_to_struct(*this, ss);
        }
        std::string toJSON() override {
            sm::reg(&Token::_id,             "id");
            sm::reg(&Token::_token,          "token");
            sm::reg(&Token::_expireDateTime, "expireDateTime");
            sm::reg(&Token::_userId,           "userId");

            sm::reg(&User::_nickname,        "nickname");
            sm::reg(&User::_password,        "password");

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
