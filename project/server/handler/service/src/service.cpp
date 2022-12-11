#include "service.hpp"
#include "structs.hpp"

#include "authorization_repository.hpp"
#include "event_repository.hpp"
#include "user_repository.hpp"
#include "session_repository.hpp"

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
int service::run_event_service(bsv query_params, std::string &response_body) {
    if (query_params.empty()) {
        Event eventExample;

        eventExample._id = 1;
        eventExample._description = "_description";
        eventExample._title = "_title";
        eventExample._dateTime = "2000-10-12";
        eventExample._maxVisitors = 13;

        Events eventsExample;

        for (int i = 0; i < 3; ++i) {
            eventsExample._events.push_back(eventExample);
        }

        response_body = eventsExample.toJSON();
    }
    return 0;
}
