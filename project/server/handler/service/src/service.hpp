#ifndef PROJECT_SERVICE_HPP
#define PROJECT_SERVICE_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
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
private:
    class AuthorizationService {
    public:
        AuthorizationService(DbManager &db_manager);

        void login(bsv query_params, std::string &response_body);

    private:
        AuthorizationRepository authorization_repository_;
    };

    class EventService {
    public:
        EventService(DbManager &db_manager);

        void event(bsv query_params, std::string &response_body);

    private:
        EventRepository event_repository_;
    };

    class SessionService {
    public:
        SessionService(DbManager &db_manager);

        void

    private:
        SessionRepository session_repository_;
    };

    class UserService {
    public:
        UserService(DbManager &db_manager);

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

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>


class service {
    class auth_service {
    private:

    };
    class event_service {
    private:
    };
    class user_service {
    private:

    };
public:

//    int run_auth_service (HCKey hcKey, boost::string_view query_params);
    int run_event_service(bsv, std::string &response_body);
//    int run_user_service (HCKey hcKey, boost::string_view query_params);
//    int run_session_service (HCKey hcKey, boost::string_view query_params);

private:
    DbManager db_manager_;
};


#endif //PROJECT_SERVICE_HPP
