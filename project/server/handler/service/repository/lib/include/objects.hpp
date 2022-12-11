#pragma once

#include <cstddef>
#include <string>


class User {
 public:
  size_t id;

  std::string nickname;  // UNIQUE
  std::string password;
  std::string email;  // UNIQUE
  std::string birth_date;  // Format: "yyyy-mm-dd"
  std::string description = "";  // ALLOW NULL
};

class Token {
 public:
  std::string token;             // UNIQUE
  std::string expire_date_time;  // Format: "yyyy-mm-dd hh:mm:ss"

  size_t user_id;
};

class Address {
 public:
  size_t id;

  std::string address;  // NOT NULL
  double longitude;  // DEFAULT NULL
  double latitude;  // DEFAULT NULL
};

class Event {
 public:
  size_t id;

  std::string title;  // NOT NULL
  std::string description;
  std::string date_time;    // Format: "yyyy-mm-dd hh:mm:ss" NOT NULL
  size_t max_visitors = 0;  // ALLOW NULL
  size_t curr_visitors = 0; // Annotation

  size_t user_id;  // NOT NULL
  Address address;  // NOT NULL
};
