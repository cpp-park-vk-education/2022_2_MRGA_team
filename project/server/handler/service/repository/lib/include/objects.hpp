#pragma once

#include <cstddef>
#include <string>

struct User {
  size_t id;

  std::string nickname;  // UNIQUE
  std::string password;
};

struct Profile {
  size_t id;

  std::string email;  // UNIQUE
  std::string birth_date;  // Format: "yyyy-mm-dd"
  std::string description = "";  // ALLOW NULL

  User user;
};

struct Token {
  size_t id;

  std::string token;             // UNIQUE
  std::string expire_date_time;  // Format: "yyyy-mm-dd hh:mm:ss"

  User user;
};

struct Address {
  size_t id;

  std::string address;
  double longitude;
  double latitude;
};

struct Event {
  size_t id;

  std::string title;
  std::string description;
  std::string date_time;    // Format: "yyyy-mm-dd hh:mm:ss"
  size_t max_visitors = 0;  // ALLOW NULL

  Address address;
};
