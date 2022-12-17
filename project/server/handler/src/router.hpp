#ifndef PROJECT_ROUTER_HPP
#define PROJECT_ROUTER_HPP


#include <functional>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <cstdlib>

#include <map>
#include <iostream>
#include <string>

#include "service.hpp"

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>

using res = http::response<http::dynamic_body>;
using req = http::request<http::dynamic_body>;


using bsv = boost::string_view;

class router {
public:
    std::map<bsv, std::function<void()>> get_handler;
    std::map<bsv, std::function<void()>> post_handler;
    std::map<bsv, std::function<void()>> put_handler;
    std::map<bsv, std::function<void()>> delete_handler;

    router(const router&) = delete;
    router(router&&) = delete;

private:
    ServiceManager& service_manager_ref;

    void events_handle               (res &response, const req &request);

    void create_event_handle         (res &response, const req &request);

    void visit_events_handle         (res &response, const req &request);

    void login_handle                (res &response, const req &request);

    void signup_handle               (res &response, const req &request);

    void logout_handle               (res &response, const req &request);

    void setting_handle              (res &response, const req &request);

public:
    explicit router                  (res &response, const req &request, ServiceManager &service_manager);

};


#endif //PROJECT_ROUTER_HPP
