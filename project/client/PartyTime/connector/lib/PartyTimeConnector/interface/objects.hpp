#ifndef CONNECTOR_OBJECTS_HPP
#define CONNECTOR_OBJECTS_HPP
#pragma once

#include <cstddef>
#include <string>
#include <optional>
#include <vector>
#include <unordered_map>

namespace {
    using std::string;
    using std::optional;
    using std::vector;
    using std::unordered_map;
    using key = string;
    using value = string;
}

class User {
public:
    size_t id;

    string nickname;  // UNIQUE
    string password;
    string email;  // UNIQUE
    string birth_date;  // Format: "yyyy-mm-dd"
    string description = "";  // ALLOW NULL
};

class Token {
public:
    size_t id;

    string token;             // UNIQUE
    string expire_date_time;  // Format: "yyyy-mm-dd hh:mm:ss"

    size_t user_id;
};

class Address {
public:
    size_t id;

    string address;
    double longitude;
    double latitude;
};

class Event {
public:
    size_t id;

    string title;
    string description;
    string date_time;    // Format: "yyyy-mm-dd hh:mm:ss"
    size_t max_visitors = 0;  // ALLOW NULL

    Address address;
};

enum Sort {
    ASC,
    DESC
};

/*принимает опциональные параметры:
limit={int}, offset={int}, order_field={str}
order_by={int}, where={key:value}*/

struct QueryParams {
    std::optional<size_t> limit;
    std::optional<size_t> offset;
    optional<vector<string>> order_fields;
    optional<Sort> sort;
    optional<unordered_map<key, value>> conditions;
};

#endif //CONNECTOR_OBJECTS_HPP
