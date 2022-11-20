#pragma once

#include <cstddef>
#include <string>

class User {
 public:
  size_t id;

  std::string nickname;  // UNIQUE
  std::string password;
};

class Profile {
 public:
  size_t id;

  std::string email;  // UNIQUE
  std::string birth_date;  // Format: "yyyy-mm-dd"
  std::string description = "";  // ALLOW NULL

  User user;
};

class Token {
 public:
  size_t id;

  std::string token;             // UNIQUE
  std::string expire_date_time;  // Format: "yyyy-mm-dd hh:mm:ss"

  User user;
};

class Address {
 public:
  size_t id;

  std::string address;
  double longitude;
  double latitude;
};

class Event {
 public:
  size_t id;

  std::string title;
  std::string description;
  std::string date_time;    // Format: "yyyy-mm-dd hh:mm:ss"
  size_t max_visitors = 0;  // ALLOW NULL

  Address address;
};
