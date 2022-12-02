#ifndef PROJECT_ROUTER_HPP
#define PROJECT_ROUTER_HPP

#include <map>
#include <string>
#include <functional>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>


namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>


using bsv = boost::string_view;

struct router {
    std::map<bsv, std::function<void(bsv)>> get_handler;
    std::map<bsv, std::function<void(bsv)>> post_handler;
    std::map<bsv, std::function<void(bsv)>> put_handler;
    std::map<bsv, std::function<void(bsv)>> delete_handler;

private:
    void login(bsv);
    void logout(bsv);
    void signup(bsv);

    void profile(bsv);
    void settings(bsv);

    void events(bsv);
    void visit_event(bsv);
    void create_event(bsv);

public:
    explicit router(bsv query_params) {
        get_handler    ["/api/v1/profile"]         = [&](bsv) {      profile(query_params);          };

        get_handler    ["/api/v1/events/"]         = [&](bsv) {      events(query_params);           };


        post_handler   ["/api/v1/auth/login"]      = [&](bsv) {      login(query_params);            };

        post_handler   ["/api/v1/auth/signup"]     = [&](bsv) {      signup(query_params);           };

        post_handler   ["/api/v1/events/visit"]    = [&](bsv) {      visit_event(query_params);      };

        post_handler   ["/api/v1/events/create"]   = [&](bsv) {      create_event(query_params);     };


        put_handler    ["/api/v1/profile/setting"] = [&](bsv) {      settings(query_params);         };


        delete_handler ["/api/v1/auth/logout"]     = [&](bsv) {      logout(query_params);           };
    }
};


#endif //PROJECT_ROUTER_HPP
