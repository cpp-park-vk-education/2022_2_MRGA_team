#pragma once

#include <cstddef>
#include <string>


class User {
 public:
  User()=default;
  User(const std::string &nickname,
      const std::string &password,
      const std::string &email,
      const std::string &birth_date,
      const std::string &description = "")
  : nickname(nickname), password(password), email(email),
  birth_date(birth_date), description(description) {}

  size_t id;

  std::string nickname;  // UNIQUE
  std::string password;
  std::string email;  // UNIQUE
  std::string birth_date;  // Format: "yyyy-mm-dd"
  std::string description = "";  // ALLOW NULL
};

class Token {
 public:
  Token()=default;
  Token(const std::string &token,
      const std::string &expire_date_time,
      const size_t &user_id)
  : token(token), expire_date_time(expire_date_time), user_id(user_id) {}

  std::string token;             // UNIQUE
  std::string expire_date_time;  // Format: "yyyy-mm-dd hh:mm:ss"

  size_t user_id;
};

class Address {
 public:
  Address()=default;
  Address(const std::string &address,
      const double &longitude = 0,
      const double &latitude = 0)
  : address(address), longitude(longitude), latitude(latitude) {}

  size_t id;

  std::string address;  // NOT NULL
  double longitude;  // DEFAULT NULL
  double latitude;  // DEFAULT NULL
};

class Event {
 public:
  Event()=default;
  Event(const std::string &title,
      const std::string &date_time,
      const size_t & user_id,
      const Address & address,
      const std::string &description = "",
      const size_t &max_visitors = 100,
      const size_t &curr_visitors = 0)
  : title(title), date_time(date_time), user_id(user_id),
  address(address), description(description),
  max_visitors(max_visitors), curr_visitors(curr_visitors) {}

  size_t id;

  std::string title;  // NOT NULL
  std::string date_time;    // Format: "yyyy-mm-dd hh:mm:ss" NOT NULL
  size_t user_id;  // NOT NULL
  Address address;  // NOT NULL

  std::string description;
  size_t max_visitors;  // ALLOW NULL DEFAULT 100
  size_t curr_visitors; // Annotation
};
