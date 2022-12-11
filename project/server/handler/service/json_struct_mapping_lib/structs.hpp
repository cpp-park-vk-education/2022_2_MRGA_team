#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <set>
#include <vector>

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
        virtual std::string toJSON() = 0;
    };

    struct User : public DBObject {
        std::string _nickname;    // UNIQUE
        std::string _password;
        std::string _email;       // UNIQUE
        std::string _birthDate;   // Format: "yyyy-mm-dd"
        std::string _description; // ALLOW NULL
    public:
        User() = default;
        User(ui id, std::string &nickname, std::string &password, std::string &email,
             std::string &birthDate, std::string &description) :
                DBObject(id),
                _nickname    (std::move(nickname)),
                _password    (std::move(password)),
                _email       (std::move(email)),
                _birthDate   (std::move(birthDate)),
                _description (std::move(description)) {};

        explicit User(const std::string &json);
        std::string toJSON() override;
    };

    struct Profile : public DBObject {
        User        _user;
        std::string _email;        // UNIQUE
        std::string _birthDate;    // Format: "yyyy-mm-dd"
        std::string _description;  // ALLOW NULL
    public:
        Profile() = default;
        Profile(ui id, std::string &email, std::string &birthDate, User &user, std::string &description = (std::string &) "") :
                DBObject(id),
                _user        (std::move(user)),
                _email       (std::move(email)),
                _birthDate   (std::move(birthDate)),
                _description (std::move(description)) {};

        explicit Profile(const std::string &json);
        std::string toJSON() override;
    };

    struct Event : public DBObject {
        //std::set<ui> _members;
        std::string    _title;
        std::string    _description;
        std::string    _dateTime;         // Format: "yyyy-mm-dd hh:mm:ss"
        ui             _maxVisitors = 0;  // ALLOW NULL
        ui             _currVisitors = 0; // Annotation
    public:
        Event() = default;
        Event(ui id,
                //std::set<ui> &members,
              std::string    &tittle,
              std::string    &description,
              std::string    &dateTime,
              ui            maxVisitors = 0,
              ui            currVisitors = 0) :

                DBObject(id),
                //_members     (std::move(members)),
                _title        (std::move(tittle)),
                _description  (std::move(description)),
                _dateTime     (std::move(dateTime)),
                _maxVisitors  (maxVisitors),
                _currVisitors (currVisitors) {};

        explicit Event(const std::string &json);
        std::string toJSON() override;
    };

    struct Events : DBObject {
        std::vector<Event> _events;

    public:
        Events() = default;
        Events(std::vector<Event> &events) :
                _events(std::move(events)) {}

        Events(const std::string &json);
        std::string toJSON() override;
    };

    struct Address : public DBObject {
        std::string _address;
        double      _longitude = 0;
        double      _latitude = 0;
    public:
        Address() = default;
        Address(ui id, std::string &address, double longitude, double latitude) :
                DBObject(id),
                _address   (std::move(address)),
                _longitude (longitude),
                _latitude  (latitude) {}

        Address(const std::string &json);
        std::string toJSON() override;
    };

    struct Token : public DBObject {
        std::string _token;           // UNIQUE
        std::string _expireDateTime;  // Format: "yyyy-mm-dd hh:mm:ss"
        User        _user;
    public:
        Token() = default;
        Token(ui id, std::string &token, std::string &expireDateTime, User& user) :
                DBObject(id),
                _token          (std::move(token)),
                _expireDateTime (std::move(expireDateTime)),
                _user           (std::move(user)) {}

        explicit Token(const std::string &json);
        std::string toJSON() override;
    };

//}


#endif  // STRUCTS_HPP
