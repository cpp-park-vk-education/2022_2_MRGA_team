#include "structs.hpp"

#include "struct_mapping.h"
#include <sstream>

std::string User::toJSON() {
    struct_mapping::reg(&User::_id, "id");
    struct_mapping::reg(&User::_nickname, "nickname");
    struct_mapping::reg(&User::_email, "email");
    struct_mapping::reg(&User::_password, "password");
    struct_mapping::reg(&User::_description, "description");
    struct_mapping::reg(&User::_age, "age");
    std::ostringstream out_json_data;
    struct_mapping::map_struct_to_json(*(this), out_json_data);
    return out_json_data.str();
}

User::User(const std::string &json) {
    struct_mapping::reg(&User::_id, "id");
    struct_mapping::reg(&User::_nickname, "nickname");
    struct_mapping::reg(&User::_email, "email");
    struct_mapping::reg(&User::_password, "password");
    struct_mapping::reg(&User::_description, "description");
    struct_mapping::reg(&User::_age, "age");
    std::stringstream ss(json);
    struct_mapping::map_json_to_struct(*this, ss);
}

std::string Party::toJSON() {
    struct_mapping::reg(&Party::_id, "id");
    struct_mapping::reg(&Party::_description, "description");
    struct_mapping::reg(&Party::_time, "time");
    struct_mapping::reg(&Party::_date, "date");
    struct_mapping::reg(&Party::_max_visitors, "max_visitors");
    struct_mapping::reg(&Party::_members, "members");
    struct_mapping::reg(&Party::_title, "title");
    struct_mapping::reg(&Party::_fk_address, "fk_address");
    std::ostringstream out_json_data;
    struct_mapping::map_struct_to_json(*(this), out_json_data);
    return out_json_data.str();
}

Party::Party(const std::string &json) {
    struct_mapping::reg(&Party::_id, "id");
    struct_mapping::reg(&Party::_description, "description");
    struct_mapping::reg(&Party::_time, "time");
    struct_mapping::reg(&Party::_date, "date");
    struct_mapping::reg(&Party::_max_visitors, "max_visitors");
    struct_mapping::reg(&Party::_members, "members");
    struct_mapping::reg(&Party::_title, "title");
    struct_mapping::reg(&Party::_fk_address, "fk_address");
    std::ostringstream out_json_data;
    std::stringstream ss(json);
    struct_mapping::map_json_to_struct(*this, ss);
}

std::string Address::toJSON() {
    struct_mapping::reg(&Address::_id, "id");
    struct_mapping::reg(&Address::_address, "address");
    struct_mapping::reg(&Address::_longitude, "longitude");
    struct_mapping::reg(&Address::_latitude, "latitude");
    std::ostringstream out_json_data;
    struct_mapping::map_struct_to_json(*(this), out_json_data);
    return out_json_data.str();
}

Address::Address(const std::string &json) {
    struct_mapping::reg(&Address::_id, "id");
    struct_mapping::reg(&Address::_address, "address");
    struct_mapping::reg(&Address::_longitude, "longitude");
    struct_mapping::reg(&Address::_latitude, "latitude");
    std::ostringstream out_json_data;
    std::stringstream ss(json);
    struct_mapping::map_json_to_struct(*this, ss);
}
