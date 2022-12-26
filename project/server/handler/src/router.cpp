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

    get_handler    ["/api/v1/events"]          = [&] () { eventsHandle(response, request); };

    get_handler    ["/api/v1/my_events"]          = [&] () { myEventsHandle(response, request); };

    get_handler    ["/api/v1/visiting_events"]          = [&] () { visitingEventsHandle(response, request); };

    post_handler   ["/api/v1/auth/login"]      = [&] () { loginHandle(response, request) ;   };

    post_handler   ["/api/v1/auth/signup"]     = [&] () { signupHandle(response, request); };
//
    post_handler   ["/api/v1/events/visit"]    = [&] () { visitEventsHandle(response, request); };

    post_handler   ["/api/v1/events/unvisit"]    = [&] () { unvisitEventsHandle(response, request); };
//
    post_handler   ["/api/v1/events/create"]   = [&]() { createEventHandle(response, request);   };

    post_handler   ["/api/v1/events/visit/update"]    = [&] () { eventUpdateHandle(response, request); };
//
//
    put_handler    ["/api/v1/profile/setting"] = [&]() { settingHandle(response, request) ;  };

    delete_handler ["/api/v1/auth/logout"]     = [&]() { logoutHandle(response, request)  ;};

    get_handler    ["/api/v1/profile"]         = [&]() {  profileHandle(response, request); };
}


void router::eventsHandle(http::response<http::dynamic_body> &response, const http::request<http::dynamic_body> &request) {
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


void router::createEventHandle(http::response<http::dynamic_body> &response, const http::request<http::dynamic_body> &request) {
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
        return;
    }
    event.user_id = userID;
    event = service_manager_ref.event_service_.createEvent(event, ec);
    if (ec.failed()) {
        response.result(http::status::gateway_timeout);
        beast::ostream(response.body()) << ec.message();
        return;
    }
    response.result(http::status::ok);
    beast::ostream(response.body()) << event.toJSON();
}


void router::visitEventsHandle(res &response, const req &request) {
    bsv token;
    try {
        token = request.at("Authorization");
    } catch (std::out_of_range &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << "Отсутствует \"Authorization\"\n";
        return;
    }
    uint userID;
    try {
        userID = service_manager_ref.session_service_.checkSession(token.to_string());
    } catch (...) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << "Ошибка авторизации\n";
        return;
    }
    char* end = nullptr;
    errno = 0;
    long long eventID= std::strtoll(beast::buffers_to_string(request.body().data()).c_str(), &end, 0);
    if (*end != '\0' || errno != 0 || eventID < 0) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Ожидается id ивента\n";
        return ;
    }
    auto ec = service_manager_ref.addVisitor(userID, eventID);
    if (ec.failed()) {
        response.result(http::status::gateway_timeout);
        beast::ostream(response.body()) << ec.message();
        return;
    }
    response.result(http::status::ok);
}


void router::unvisitEventsHandle(res &response, const req &request) {
    bsv token;
    try {
        token = request.at("Authorization");
    } catch (std::out_of_range &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << "Отсутствует \"Authorization\"\n";
        return;
    }
    uint userID;
    try {
        userID = service_manager_ref.session_service_.checkSession(token.to_string());
    } catch (...) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << "Ошибка авторизации\n";
        return;
    }
    char* end = nullptr;
    errno = 0;
    long long eventID= std::strtoll(beast::buffers_to_string(request.body().data()).c_str(), &end, 0);
    if (*end != '\0' || errno != 0 || eventID < 0) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Ожидается id ивента\n";
        return;
    }
    auto ec = service_manager_ref.deleteVisitor(userID, eventID);
    if (ec.failed()) {
        response.result(http::status::gateway_timeout);
        beast::ostream(response.body()) << ec.message();
    }
    response.result(http::status::ok);
}


void router::loginHandle(res &response, const req &request) {
    error_code ec;
    User user = User::fromJSON(beast::buffers_to_string(request.body().data()), ec);
    if (ec.failed()) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Некорректные данные\n";
        return;
    }
    bool successLoginOperation;
    ec = service_manager_ref.auth_service_.checkPassword(user, successLoginOperation);
    if (ec.failed()) {
        response.result(http::status::gateway_timeout);
        beast::ostream(response.body()) << ec.message();
        return;
    }
    if (!successLoginOperation) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Не верный логин или пароль\n";
        return;
    }
    Token token;
    ec = service_manager_ref.createToken(user, token);
    if (ec.failed()) {
        response.result(http::status::gateway_timeout);
        beast::ostream(response.body()) << ec.message();
        return;
    }
    response.result(http::status::ok);
    beast::ostream(response.body()) << token.toJSON();
}


void router::signupHandle(res &response, const req &request) {
    error_code ec;
    User user = User::fromJSON(beast::buffers_to_string(request.body().data()), ec);
    if (ec.failed()) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Некорректные данные";
        return;
    }
    bool login_exist;
    ec = service_manager_ref.auth_service_.loginExist(user.nickname, login_exist);
    if (ec.failed()) {
        response.result(http::status::gateway_timeout);
        beast::ostream(response.body()) << ec.message();
        return;
    }
    if (login_exist) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Такой пользователь уже существует";
        return;
    }
    ec = service_manager_ref.auth_service_.signupUser(user);
    if (ec.failed()) {
        response.result(http::status::gateway_timeout);
        beast::ostream(response.body()) << ec.message();
        return;
    }
    Token token;
    ec = service_manager_ref.createToken(user, token);
    if (ec.failed()) {
        response.result(http::status::gateway_timeout);
        beast::ostream(response.body()) << ec.message();
        return;
    }
    response.result(http::status::ok);
    beast::ostream(response.body()) << token.toJSON();
}

void router::logoutHandle(res &response, const req &request) {

}

void router::settingHandle(res &response, const req &request) {

}

void router::myEventsHandle(res &response, const req &request) {
    bsv tokenString;
    try {
        tokenString = request.at("Authorization");
    } catch (std::out_of_range &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << "Отсутствует \"Authorization\"\n";
        return;
    }
    uint userId;
    try {
        userId = service_manager_ref.session_service_.checkSession(tokenString.to_string());
    } catch (std::invalid_argument &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << ex.what();
        return;
    }
    error_code ec;
    auto eventsVector = service_manager_ref.event_service_.myEvents(userId, ec);
    if (ec.failed()) {
        response.result(http::status::gateway_timeout);
        beast::ostream(response.body()) << ec.message();
        return;
    }
    response.result(http::status::ok);
    beast::ostream(response.body()) << eventsVector.toJSON();
}

void router::visitingEventsHandle(res &response, const req &request) {
    bsv tokenString;
    try {
        tokenString = request.at("Authorization");
    } catch (std::out_of_range &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << "Отсутствует \"Authorization\"\n";
        return;
    }
    uint userId;
    try {
        userId = service_manager_ref.session_service_.checkSession(tokenString.to_string());
    } catch (std::invalid_argument &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << ex.what();
        return;
    }
    error_code ec;
    auto eventsVector = service_manager_ref.event_service_.visitingEvents(userId, ec);
    if (ec.failed()) {
        response.result(http::status::gateway_timeout);
        beast::ostream(response.body()) << ec.message();
        return;
    }
    response.result(http::status::ok);
    beast::ostream(response.body()) << eventsVector.toJSON();
}

void router::eventUpdateHandle(res &response, const req &request) {
    bsv tokenString;
    try {
        tokenString = request.at("Authorization");
    } catch (std::out_of_range &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << "Отсутствует \"Authorization\"\n";
        return;
    }
    uint userId;
    try {
        userId = service_manager_ref.session_service_.checkSession(tokenString.to_string());
    } catch (std::invalid_argument &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << ex.what();
        return;
    }
    error_code ec;
    Event event = Event::fromJSON(beast::buffers_to_string(request.body().data()), ec);
    if (ec.failed()) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Некорректные данные\n";
        return;
    }
    if (event.user_id != userId) {
        response.result(http::status::forbidden);
        beast::ostream(response.body()) << "У пользователя нет прав\n";
        return;
    }
    service_manager_ref.event_service_.update_event_data(event, ec);
    if (ec.failed()) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Ошибка на стороне бд\n";
        return;
    }
    response.result(http::status::ok);
    beast::ostream(response.body()) << event.toJSON();
}

void router::profileSettingsHandle(res &response, const req &request) {
    bsv tokenString;
    try {
        tokenString = request.at("Authorization");
    } catch (std::out_of_range &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << "Отсутствует \"Authorization\"\n";
        return;
    }
    uint userId;
    try {
        userId = service_manager_ref.session_service_.checkSession(tokenString.to_string());
    } catch (std::invalid_argument &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << ex.what();
        return;
    }
    User user;
    try {
        user = service_manager_ref.user_service_.getUserData(userId);
    } catch (...) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Ошибка на стороне бд\n";
        return;
    }
    response.result(http::status::ok);
    beast::ostream(response.body()) << user.toJSON();
}

void router::profileUpdateHandle(res &response, const req &request) {
    bsv tokenString;
    try {
        tokenString = request.at("Authorization");
    } catch (std::out_of_range &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << "Отсутствует \"Authorization\"\n";
        return;
    }
    uint userId;
    try {
        userId = service_manager_ref.session_service_.checkSession(tokenString.to_string());
    } catch (std::invalid_argument &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << ex.what();
        return;
    }
    error_code ec;
    User user = User::fromJSON(beast::buffers_to_string(request.body().data()), ec);
    if (ec.failed()) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Некорректные данные\n";
        return;
    }
    try {
        service_manager_ref.user_service_.updateUserData(user);
    } catch (...) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Ошибка на стороне бд\n";
        return;
    }
    response.result(http::status::ok);
    beast::ostream(response.body()) << user.toJSON();
}

void router::profileHandle(res &response, const req &request) {
    bsv tokenString;
    try {
        tokenString = request.at("Authorization");
    } catch (std::out_of_range &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << "Отсутствует \"Authorization\"\n";
        return;
    }
    uint userId;
    try {
        userId = service_manager_ref.session_service_.checkSession(tokenString.to_string());
    } catch (std::invalid_argument &ex) {
        response.result(http::status::unauthorized);
        beast::ostream(response.body()) << ex.what();
        return;
    }
    User user;
    try {
        user = service_manager_ref.user_service_.getUserData(userId);
    } catch (...) {
        response.result(http::status::bad_request);
        beast::ostream(response.body()) << "Ошибка на стороне бд\n";
        return;
    }
    response.result(http::status::ok);
    beast::ostream(response.body()) << user.toJSON();
}



