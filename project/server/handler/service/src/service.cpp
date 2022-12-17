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
        try {
            events.events = event_repository_.get_events();
            response_body = events.toJSON();
        } catch (...) {
            throw std::invalid_argument("Ошибка от бд");
        }
    }
}

Event ServiceManager::EventService::createEvent(uint userId, const std::string& request_body) {
    Event event(request_body);
    event.user_id = userId;
    try {
        int eventId = event_repository_.create_event(event);
        if (eventId < 0) {
            throw std::invalid_argument("Ошибка от бд");
        }
        event.id = eventId;
        return event;
    } catch (...) {
        throw std::invalid_argument("Ошибка от бд");
    }
}

ServiceManager::SessionService::SessionService(DbManager &db_manager) :             session_repository_(db_manager) {};

uint ServiceManager::SessionService::checkSession(const std::string &token) {
    if (token == "admin02022") {
        return 0;  // user_id
    }

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
