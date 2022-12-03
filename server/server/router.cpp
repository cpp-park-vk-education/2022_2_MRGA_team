#include "router.hpp"

router::router(bsv query_params) {

    get_handler    ["/api/v1/profile/index.html"]         = [&](bsv) {   service_->run_user_service(query_params);    };

    get_handler    ["/api/v1/events/index.html"]          = [&](bsv) {   service_->run_event_service(query_params);   };


    post_handler   ["/api/v1/auth/login/index.html"]      = [&](bsv) {   service_->run_auth_service(query_params);    };

    post_handler   ["/api/v1/auth/signup/index.html"]     = [&](bsv) {   service_->run_auth_service(query_params);    };

    post_handler   ["/api/v1/events/visit/index.html"]    = [&](bsv) {   service_->run_event_service(query_params);   };

    post_handler   ["/api/v1/events/create/index.html/"]  = [&](bsv) {   service_->run_event_service(query_params);   };


    put_handler    ["/api/v1/profile/setting/index.html"] = [&](bsv) {   service_->run_user_service(query_params);    };


    delete_handler ["/api/v1/auth/logout/index.html"]     = [&](bsv) {   service_->run_auth_service(query_params);    };
}
