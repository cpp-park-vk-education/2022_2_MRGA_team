#include "service.hpp"
#include "structs.hpp"

#include "authorization_repository.hpp"
#include "event_repository.hpp"
#include "user_repository.hpp"
#include "session_repository.hpp"



ServiceManager::AuthorizationService::AuthorizationService(DbManager &db_manager) : authorization_repository_(db_manager) {}

ServiceManager::EventService::EventService(DbManager &db_manager) :                 event_repository_(db_manager) {}

void ServiceManager::EventService::event(bsv query_params, string &response_body) {
    if (query_params.empty()) {
        Events events;
        events.events = event_repository_.get_events();
        response_body = events.toJSON();
    }
}

void ServiceManager::EventService::createEvent(uint userId, std::string request_body) {
    Event event(request_body);
    event.user_id = userId;
    int result = event_repository_.create_event(event);
    if (result == -1) {
        throw std::invalid_argument("Ошибка от бд");
    }
}

ServiceManager::SessionService::SessionService(DbManager &db_manager) :             session_repository_(db_manager) {};

uint ServiceManager::SessionService::checkSession(const std::string &token) {
    int result = session_repository_.check_token(token);
    if (result == -1) {
        throw std::invalid_argument("токен не валидный");
    }
    Token tok;
    tok.token = token;
    try {
        User user = session_repository_.get_user_by_token(tok);
        return user.id;
    } catch (...) {
        throw std::invalid_argument("такого id пользователя не существует");
    }
}    
ServiceManager::UserService::UserService(DbManager &db_manager) :                   user_repository_(db_manager) {};




//int service::run_auth_service(HCKey hcKey, boost::string_view query_params) {
//    Profile p(query_params.to_string());
//    switch (hcKey) {
//        case HCKey::logout :
//            std::make_shared<AuthorizationRepository>(*db_manager_)->check_password(p._id, p._user._password);
//            break;
//
//        case HCKey::login :
//            std::make_shared<AuthorizationRepository>(*db_manager_)->existence_email(p._email);
//            break;
//
//        case HCKey::profile :
//            std::make_shared<AuthorizationRepository>(*db_manager_)->existence_nickname(p._user._nickname);
//            break;
//
//        default:
//            throw ;
//    }
//    return 0;
//}
//

//
//int service::run_user_service(HCKey hcKey, boost::string_view query_params) {
//    User u(query_params.to_string());
//    Event e(query_params.to_string());
//    // структура тут не нужна, она будет нужна только при выводе из функции
//    switch (hcKey) {
//        case HCKey::logout :
//            std::make_shared<UserRepository>(*db_manager_)->get_user_data(u._id);
//            break;
//
//        case HCKey::login :
//            std::make_shared<UserRepository>(*db_manager_)->update_user_data(u);
//            break;
//
//        case HCKey::profile :
//            std::make_shared<UserRepository>(*db_manager_)->add_visitor(e._id, u._id);
//            break;
//
//        default:
//            throw;
//    }
//    return 0;
//}
//
//int service::run_session_service(HCKey hcKey, boost::string_view query_params) {
//    Token t(query_params.to_string());
//    User u(query_params.to_string());
//    // структура тут не нужна, она будет нужна только при выводе из функции
//    switch (hcKey) {
//        case HCKey::logout :
//            std::make_shared<SessionRepository>(*db_manager_)->create_token(u._id);
//            break;
//
//        case HCKey::login :
//            std::make_shared<SessionRepository>(*db_manager_)->delete_token(t);
//            break;
//
//        case HCKey::profile :
//            std::make_shared<SessionRepository>(*db_manager_)->get_tokens(u._id);
//            break;
//
//        default:
//            throw;
//    }
//    return 0;
//}

ServiceManager::ServiceManager()
    : db_manager_{DbManager()},
      auth_service_(db_manager_),
      event_service_(db_manager_),
      user_service_(db_manager_),
      session_service_(db_manager_) {}

ServiceManager::ServiceManager(DbManager &db_manager)
    : db_manager_{db_manager},
      auth_service_(db_manager_),
      event_service_(db_manager_),
      user_service_(db_manager_),
      session_service_(db_manager_) {}
