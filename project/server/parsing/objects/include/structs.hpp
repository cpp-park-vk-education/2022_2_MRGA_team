#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <set>

class dbObject {
protected:
    uint _id;
public:
    virtual std::string toJSON() = 0;
};

class User : public dbObject {
    std::string _nickname;
    std::string _email;
    std::string _password;
    std::string _description;
    int _age;
public:
    std::string toJSON() override;
    User(const std::string &json);
};

class Party : public dbObject {
    std::set<size_t> _members;
    std::string _title;
    std::string _description;
    std::string _date;
    std::string _time;
    uint _max_visitors;

    uint _fk_address;
public:
    std::string toJSON() override;
    Party(const std::string &json);
};

class Address : public dbObject {
    std::string _address;
    double _longitude;
    double _latitude;
public:
    std::string toJSON() override;
    Address(const std::string &json);
};

#endif  // STRUCTS_HPP
