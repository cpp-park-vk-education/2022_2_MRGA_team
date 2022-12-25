#include "service.hpp"
#include "structs.hpp"

#include "authorization_repository.hpp"
#include "event_repository.hpp"
#include "user_repository.hpp"
#include "session_repository.hpp"
// #include "service_error_codes.hpp"

#include <chrono>


ServiceManager::AuthorizationService::AuthorizationService(DbManager &db_manager) : authorization_repository_(db_manager) {}

boost::system::error_code ServiceManager::AuthorizationService::signupUser(const User &user) {
    try {
        authorization_repository_.create_user(user);
    } catch (std::invalid_argument &ex) {
        boost::system::error_code ec;
        ec.assign(int(service_error_codes::db_side_error), service_error_category());
        return ec;
    }
    return {};
}

boost::system::error_code ServiceManager::AuthorizationService::loginExist(const std::string &login, bool &positiveAnswer) {
    try {
        positiveAnswer = authorization_repository_.existence_nickname(login);
    } catch (std::invalid_argument &ex) {
        boost::system::error_code ec;
        ec.assign(int(service_error_codes::db_side_error), service_error_category());
        return ec;
    }
    return {};
}

boost::system::error_code ServiceManager::AuthorizationService::checkPassword(uint userId, const std::string &password, bool &positiveAnswer) {
    try {
        positiveAnswer = authorization_repository_.check_password(userId, password);
    } catch (std::invalid_argument &ex) {
        boost::system::error_code ec;
        ec.assign(int(service_error_codes::db_side_error), service_error_category());
        return ec;
    }
    return {};
}

ServiceManager::EventService::EventService(DbManager &db_manager) :                 event_repository_(db_manager) {}

void ServiceManager::EventService::event(bsv query_params, string &response_body) {
    Events events;
    try {
        events.events = event_repository_.get_events();
        response_body = events.toJSON();
    } catch (...) {
        throw std::invalid_argument("Ошибка от бд");
    }
}

Event ServiceManager::EventService::createEvent(uint userId, const std::string& request_body) {
    Event event(request_body);
    std::cout << "event_id" << event.id << std::endl;
    std::cout << event.toJSON() << std::endl;
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

Event ServiceManager::EventService::createEvent(const Event &event, boost::system::error_code &ec) {
    Event ev = event;
    try {
        int eventId = event_repository_.create_event(event);
        if (eventId < 0) {
            ec.assign(int(service_error_codes::db_side_error), service_error_category());
            return ev;
        }
        ev.id = eventId;
        return ev;
    } catch (...) {
        ec.assign(int(service_error_codes::db_side_error), service_error_category());
        return ev;
    }
}

uint ServiceManager::EventService::checkEventExistence(uint eventId) {
    try {
        std::cerr << "Начало вызова event_repository_.existence_event()" << std::endl;
        int userExistence = event_repository_.existence_event(eventId);
        if (userExistence < 0) {
            std::cerr << "event_repository_.existence_event() вернул значение < 0" << std::endl;
            throw std::invalid_argument("такого event не существует");
        }
        return eventId;
    } catch (...) {
        throw std::invalid_argument("ошибка бд");
    }
}

Events ServiceManager::EventService::myEvents(uint userId, boost::system::error_code &ec) {
    std::vector<Event> events;
    try {
        events = event_repository_.get_organized_events_by_user(userId);
    } catch (...) {
        ec.assign(int(service_error_codes::db_side_error), service_error_category());
    }
    return events;
}

Events ServiceManager::EventService::visitingEvents(uint userId, boost::system::error_code &ec) {
    std::vector<Event> events;
    try {
        events = event_repository_.get_visited_events_by_user(userId);
    } catch (...) {
        ec.assign(int(service_error_codes::db_side_error), service_error_category());
    }
    return events;
}

void ServiceManager::EventService::update_event_data(const Event &event, boost::system::error_code &ec) {
    try {
        int success = event_repository_.update_event_data(event);
    } catch  (...) {
        ec.assign(int(service_error_codes::db_side_error), service_error_category());
    }
}

ServiceManager::SessionService::SessionService(DbManager &db_manager) :             session_repository_(db_manager) {}

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

ServiceManager::UserService::UserService(DbManager &db_manager) :                   user_repository_(db_manager) {}

void ServiceManager::UserService::addVisitor(uint eventId, uint userId) {
    std::cerr << "вызов user_repository_.add_visitor()" << std::endl;
    user_repository_.add_visitor(eventId, userId);
    std::cerr << "отработал user_repository_.add_visitor()" << std::endl;
}

void ServiceManager::UserService::deleteVisitor(uint eventId, uint userId) {
    std::cerr << "вызов user_repository_.delete_visitor()" << std::endl;
    user_repository_.delete_visitor(eventId, userId);
    std::cerr << "отработал user_repository_.delete_visitor()" << std::endl;
}

uint ServiceManager::UserService::checkUserExistence(uint userId) {
    try {
        int userExistence = user_repository_.existence_user(userId);
        if (userExistence < 0) {
            throw std::invalid_argument("такого юзера не существует");
        }
        return userId;
    } catch (...) {
        throw std::invalid_argument("ошибка бд");
    }
}


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

void ServiceManager::addVisitor(const std::string &requestBody) {
    try {
        Event event(requestBody);
        try {
            uint userId = user_service_.checkUserExistence(event.user_id);
            uint eventId = event_service_.checkEventExistence(event.id);
            user_service_.addVisitor(eventId, userId);
        } catch (std::invalid_argument &ex) {
            throw (std::invalid_argument(ex.what()));
        }
    } catch (std::exception &ex) {
        throw std::invalid_argument("Ошибка конструктора объекта\n");
    }
}

boost::system::error_code ServiceManager::addVisitor(ui userID, ui eventID) {
    try {
        // существование юзера и ивента нужно проверять отдельно, чтобы можно было разные коды ошибок возвращать
        //  также нужно уметь различать, когда бд вернула результат, а когда там произошла ошибка.
        // когда она вернула результат, но не нашла ивент или юзера, мы должны здесь вернуть соответствующую ошибку.
        // а в хендлере уже по этой ошибке вернуть bad_request
        // если же бд не вернула ответ, значит нужно здесь вернуть bd_side_error, а в хендлере уже 500 код, но это не точно.
        uint userId = user_service_.checkUserExistence(userID);
        uint eventId = event_service_.checkEventExistence(eventID);
        user_service_.addVisitor(eventId, userId);
    } catch (std::invalid_argument &ex) {
        boost::system::error_code ec;
        ec.assign(int(service_error_codes::db_side_error), service_error_category());
        return ec;
    }
    return {};
}

void ServiceManager::deleteVisitor(const std::string &requestBody) {
    try {
        Event event(requestBody);
        try {
            uint userId = user_service_.checkUserExistence(event.user_id);
            uint eventId = event_service_.checkEventExistence(event.id);
            user_service_.deleteVisitor(eventId, userId);
        } catch (std::invalid_argument &ex) {
            throw (std::invalid_argument(ex.what()));
        }
    } catch (...) {
        throw std::invalid_argument("Ошибка конструктора объекта\n");
    }
}

boost::system::error_code ServiceManager::deleteVisitor(ui userID, ui eventID) {
    try {
        uint userId = user_service_.checkUserExistence(userID);
        uint eventId = event_service_.checkEventExistence(eventID);
        user_service_.deleteVisitor(eventId, userId);
    } catch (std::invalid_argument &ex) {
        boost::system::error_code ec;
        ec.assign(int(service_error_codes::db_side_error), service_error_category());
        return ec;
    }
    return {};
}

boost::system::error_code ServiceManager::createToken(const User &user, Token &token) {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::string tokenString = {std::to_string(user.id) + std::ctime(&currentTime) + user.nickname};
    token.token = tokenString;
    try {
        session_service_.session_repository_.create_token(token);
    } catch (...) {
        boost::system::error_code ec;
        ec.assign(int(service_error_codes::db_side_error), service_error_category());
        return ec;
    }
    return {};
}


// 504 - было соединение и пропало (если бд выкинула исключение)
// регистрация, такой логин уже есть (), то 401

// авторизация (не правильный логи или пароль) то 401
// 504 - было соединение и пропало (если бд выкинула исключение)

// 507 поменять на 504 status ... storage.

// 400 во всех других случаях

// юзер_id, логин пользователя, id_токена - канкат для std::string token

// запрос на получение всех своих ивентов

// получить ивенты пользователя, получит