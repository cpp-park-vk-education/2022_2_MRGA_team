#include "router.hpp"

router::router(bsv query_params) {

    get_handler    ["/api/v1/profile"]         = [&](bsv) {   service_->run_user_service(query_params);    };

    get_handler    ["/api/v1/events"]          = [&](bsv) {   service_->run_event_service(query_params);   };


    post_handler   ["/api/v1/auth/login"]      = [&](bsv) {   service_->run_auth_service(query_params);    };

    post_handler   ["/api/v1/auth/signup"]     = [&](bsv) {   service_->run_auth_service(query_params);    };

    post_handler   ["/api/v1/events/visit"]    = [&](bsv) {   service_->run_event_service(query_params);   };

    post_handler   ["/api/v1/events/create"]   = [&](bsv) {   service_->run_event_service(query_params);   };


    put_handler    ["/api/v1/profile/setting"] = [&](bsv) {   service_->run_user_service(query_params);    };


    delete_handler ["/api/v1/auth/logout"]     = [&](bsv) {   service_->run_auth_service(query_params);    };
}
