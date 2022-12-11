#include "structs.hpp"

#include "struct_mapping.hpp"
#include <sstream>

/* ========== USER ========== */

//namespace structs {

    std::string User::toJSON() {
        sm::reg(&User::_id,       "id");
        sm::reg(&User::_nickname, "nickname");
        sm::reg(&User::_password, "password");

        std::ostringstream outJsonData;
        sm::map_struct_to_json(*(this), outJsonData);
        return outJsonData.str();
    }

    User::User(const std::string &json) {
        sm::reg(&User::_id,       "id");
        sm::reg(&User::_nickname, "nickname");
        sm::reg(&User::_password, "password");

        std::stringstream ss(json);
        sm::map_json_to_struct(*this, ss);
    }

/* ========== PROFILE ========== */

    std::string Profile::toJSON() {
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

    Profile::Profile(const std::string &json) {
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

/* ========== EVENT ========== */

    std::string Event::toJSON() {
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

    Event::Event(const std::string &json) {
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

/* ========== EVENTS ========== */

    std::string Events::toJSON() {

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

    Events::Events(const std::string &json) {

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

/* ========== ADDRESS ========== */

    std::string Address::toJSON() {
        sm::reg(&Address::_id,        "id");
        sm::reg(&Address::_address,   "address");
        sm::reg(&Address::_longitude, "longitude");
        sm::reg(&Address::_latitude,  "latitude");

        std::ostringstream outJsonData;
        sm::map_struct_to_json(*(this), outJsonData);
        return outJsonData.str();
    }

    Address::Address(const std::string &json) {
        sm::reg(&Address::_id,        "id");
        sm::reg(&Address::_address,   "address");
        sm::reg(&Address::_longitude, "longitude");
        sm::reg(&Address::_latitude,  "latitude");

        std::stringstream ss(json);
        sm::map_json_to_struct(*this, ss);
    }

/* ========== TOKEN ========== */

    std::string Token::toJSON() {
        sm::reg(&Token::_id,             "id");
        sm::reg(&Token::_token,          "token");
        sm::reg(&Token::_expireDateTime, "expireDateTime");
        sm::reg(&Token::_user,           "user");

        sm::reg(&User::_nickname,        "nickname");
        sm::reg(&User::_password,        "password");

        std::ostringstream outJsonData;
        sm::map_struct_to_json(*(this), outJsonData);
        return outJsonData.str();
    }

    Token::Token(const std::string &json) {
        sm::reg(&Token::_id,             "id");
        sm::reg(&Token::_token,          "token");
        sm::reg(&Token::_expireDateTime, "expireDateTime");
        sm::reg(&Token::_user,           "user");

        sm::reg(&User::_nickname,        "nickname");
        sm::reg(&User::_password,        "password");

        std::stringstream ss(json);
        sm::map_json_to_struct(*this, ss);
    }

//}

