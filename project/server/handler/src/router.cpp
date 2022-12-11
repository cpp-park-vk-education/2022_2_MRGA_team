#include "router.hpp"

router::router(bsv query_params, std::string &response_body) : _query_params(query_params) {

    //get_handler    ["/api/v1/profile"]         = [&](bsv) {   service_->run_user_service(hcKey, query_params);    };

    get_handler    ["/api/v1/events"]          = [&] () { events_handle(response_body); };

//    post_handler   ["/api/v1/auth/login"]      = [&](bsv) {   service_->run_auth_service(hcKey, query_params);    };
//
//    post_handler   ["/api/v1/auth/signup"]     = [&](bsv) {   service_->run_auth_service(hcKey, query_params);    };
//
//    post_handler   ["/api/v1/events/visit"]    = [&](bsv) {   service_->run_event_service(hcKey, query_params);   };
//
//    post_handler   ["/api/v1/events/create"]   = [&](bsv) {   service_->run_event_service(hcKey, query_params);   };
//
//
//    put_handler    ["/api/v1/profile/setting"] = [&](bsv) {   service_->run_user_service(hcKey, query_params);    };
//
//
//    delete_handler ["/api/v1/auth/logout"]     = [&](bsv) {   service_->run_auth_service(hcKey, query_params);    };
}

void router::events_handle(std::string &response_body) {
    //if (_query_params.empty()) {

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
    //}
}
