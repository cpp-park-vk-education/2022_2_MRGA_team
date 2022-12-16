#include "router.hpp"

#define BOOST_URL_NO_LIB
#include <boost/url.hpp>

using namespace boost::urls;

router::router(http::response<http::dynamic_body> &response,
               const http::request<http::dynamic_body> &request,
               ServiceManager &service_manager)

               : service_manager_ref(service_manager)

{

    //get_handler    ["/api/v1/profile"]         = [&](bsv) {   service_->run_user_service(hcKey, query_params);    };

    get_handler    ["/api/v1/events"]          = [&] () { events_handle(response, request); };

    post_handler   ["/api/v1/auth/login"]      = [&] () {   login_handle(response, request) ;   };

    post_handler   ["/api/v1/auth/signup"]     = [&] () { signup_handle(response, request); };
//
    post_handler   ["/api/v1/events/visit"]    = [&] () {   visit_events_handle(response, request); };
//
    post_handler   ["/api/v1/events/create"]   = [&]() {  create_event_handle(response, request);   };
//
//
    put_handler    ["/api/v1/profile/setting"] = [&]() {    setting_handle(response, request) ;  };


    delete_handler ["/api/v1/auth/logout"]     = [&]() {     logout_handle(response, request)  ;};
}

void router::events_handle(http::response<http::dynamic_body> &response, const http::request<http::dynamic_body> &request) {

    std::cerr << "=========ЗАПРОС ПРИШЕЛ В GET HANDLE==========" << std::endl;

    boost::url url = parse_uri_reference(request.target()).value();

    std::string response_body;

    if (url.query().empty()) {
        service_manager_ref.event_service_.event(url.query(), response_body);
    } else {
        /// сервис авторизации, сервис ивентов
    }

    // проверяем код ошибки
    if (true) {
        response.result(http::status::ok);
        beast::ostream(response.body()) << response_body;

    } else {
        // ошибка бд
    }
}

void router::create_event_handle(http::response<http::dynamic_body> &response, const http::request<http::dynamic_body> &request) {

}

void router::visit_events_handle(res &response, const req &request) {

}

void router::login_handle(res &response, const req &request) {

}

void router::signup_handle(res &response, const req &request) {

}

void router::logout_handle(res &response, const req &request) {

}

void router::setting_handle(res &response, const req &request) {

}

