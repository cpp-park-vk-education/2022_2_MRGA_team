#include "service.hpp"

int service::run_auth_service(boost::string_view query_params) {
    if (1) {
        std::make_shared<AuthorizationRepository>(*db_manager_)->check_password();
    }

    return 0;
}

int service::run_event_service(boost::string_view query_params) {
    return 0;
}

int service::run_user_service(boost::string_view query_params) {
    return 0;
}
