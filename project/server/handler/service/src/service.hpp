#ifndef PROJECT_SERVICE_HPP
#define PROJECT_SERVICE_HPP

#include <boost/beast/core.hpp>
//#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>
//#include <boost/asio/connect.hpp>
//#include <boost/asio/ip/tcp.hpp>
//#include <cstdlib>
#include <iostream>
#include <string>

#include "db_manager.hpp"
#include "constants.hpp"

#include "authorization_repository.hpp"
#include "event_repository.hpp"
#include "session_repository.hpp"
#include "user_repository.hpp"

using bsv = boost::string_view;

class ServiceManager {
public:
    ServiceManager();
    explicit ServiceManager(DbManager &db_manager);
private:
    class AuthorizationService {
    public:
        explicit AuthorizationService(DbManager &db_manager);

    private:
        AuthorizationRepository authorization_repository_;
    };

    class EventService {
    public:
        explicit EventService(DbManager &db_manager);

        void event(bsv query_params, std::string &response_body);

	Event createEvent(uint userId, const std::string& request_body);

    private:
        EventRepository event_repository_;

    };

    class SessionService {
    public:
        explicit SessionService(DbManager &db_manager);

	uint checkSession(const std::string &token);

    private:
        SessionRepository session_repository_;
    };

    class UserService {
    public:
        explicit UserService(DbManager &db_manager);

    private:
        UserRepository user_repository_;
    };
public:
    AuthorizationService auth_service_;
    EventService         event_service_;
    SessionService       session_service_;
    UserService          user_service_;

private:
    DbManager db_manager_;
};

//namespace beast = boost::beast;     // from <boost/beast.hpp>
//namespace http = beast::http;       // from <boost/beast/http.hpp>
//namespace net = boost::asio;        // from <boost/asio.hpp>
//using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>



#endif //PROJECT_SERVICE_HPP
