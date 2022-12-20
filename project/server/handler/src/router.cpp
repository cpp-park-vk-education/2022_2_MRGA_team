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

    post_handler   ["/api/v1/events/unvisit"]    = [&] () {   unvisit_events_handle(response, request); };
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
    bsv token;
    try {
        token = request.at("Authorization");
    } catch (std::out_of_range &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << "нет хедера с токеном";
        return;
    }
    uint userID;
    try {
        userID = service_manager_ref.session_service_.checkSession(token.to_string());
    } catch (...) {
        response.result(http::status::forbidden);
        beast::ostream(response.body()) << "Ошибка авторизации";
        return;
    }
    error_code ec;
    Event event = Event::fromJSON(beast::buffers_to_string(request.body().data()), ec);
    if (ec.failed()) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << ec.message();
        return ;
    }
    event.user_id = userID;
    event = service_manager_ref.event_service_.createEvent(event, ec);
    if (ec.failed()) {
        response.result(http::status::insufficient_storage);
        beast::ostream(response.body()) << ec.message();
        return ;
    }
    response.result(http::status::ok);
    beast::ostream(response.body()) << event.toJSON();
    return ;
}







    // std::string token = equest.at("Authorization"); // check this
    // int res = service_manager_ref.session_service_.session_repository_.check_token(token);
    // if (!res) {
    //     response.result(http::status::unauthorized);
    //     beast::ostream(response.body()) << "вы не авторизованы";
    //     return ;
    // }
    // Token tok;
    // tok.token = token;
    // User user =  service_manager_ref.session_service_.session_repository_.get_user_by_token(tok);
    // Event event(beast::buffers_to_string(request.body()));
    // event.user_id = user.id;

    // //res = service_manager_ref.event_service_.create_event(event);


void router::visit_events_handle(res &response, const req &request) {
    std::cerr << "=========ЗАПРОС ПРИШЕЛ В VISIT EVENTS HANDLE==========" << std::endl;
    try {
        bsv token = request.at("Authorization");
        try {
            service_manager_ref.session_service_.checkSession(token.to_string());
            try {
                service_manager_ref.addVisitor(beast::buffers_to_string(request.body().data()));
                response.result(http::status::ok);
                return;
            } catch (std::exception &ex) {
                response.result(http::status::unauthorized);
                beast::ostream(response.body()) << ex.what();
                return;
            }
        } catch (...) {
            response.result(http::status::unauthorized);
            beast::ostream(response.body()) << "Ошибка авторизации";
            return;
        }
    } catch (std::out_of_range &ex) {
        response.result(http::status::forbidden);
        beast::ostream(response.body()) << "нет хедера с токеном";
        return;
    }
}

void router::unvisit_events_handle(res &response, const req &request) {
    std::cerr << "=========ЗАПРОС ПРИШЕЛ В UNVISIT EVENTS HANDLE==========" << std::endl;
    try {
        bsv token = request.at("Authorization");
        try {
            service_manager_ref.session_service_.checkSession(token.to_string());
            try {
                service_manager_ref.deleteVisitor(beast::buffers_to_string(request.body().data()));
                response.result(http::status::ok);
                // beast::ostream(response.body()) << event.toJSON();
                return;
            } catch (std::exception &ex) {
                response.result(http::status::unauthorized);
                beast::ostream(response.body()) << ex.what();
                return;
            }
        } catch (...) {
            response.result(http::status::unauthorized);
            beast::ostream(response.body()) << "Ошибка авторизации";
            return;
        }
    } catch (std::out_of_range &ex) {
        response.result(http::status::forbidden);
        beast::ostream(response.body()) << "нет хедера с токеном";
        return;
    }
}

void router::login_handle(res &response, const req &request) {

}

void router::signup_handle(res &response, const req &request) {

}

void router::logout_handle(res &response, const req &request) {

}

void router::setting_handle(res &response, const req &request) {

}



