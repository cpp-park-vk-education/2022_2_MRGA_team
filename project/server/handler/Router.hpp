#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <functional>
#include <map>
#include <string>

class Router {
    std::map<std::string, std::function<void()>> get_hendlers;
    std::map<std::string, std::function<void()>> post_hendlers;
    std::map<std::string, std::function<void()>> delete_hendlers;
    std::map<std::string, std::function<void()>> put_hendlers;

    
};

class Service {

};

class AuthService : Service {

};

class UserService : Service {

};

class EventService : Service {

};

#endif // ROUTER_HPP
