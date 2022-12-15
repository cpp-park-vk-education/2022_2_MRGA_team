#include "EventsConnector.hpp"
#include "api.h"

EventsConnector::EventsConnector
    (shared_ptr<ILocalStorage> &store, shared_ptr<IHttpConnector> &connector): store(store), connector(connector) {}

Response<optional<vector<Event>>> EventsConnector::events() {
    PartyTimeApi api;
    Response<optional<vector<Event>>> resp;
    auto res = this->connector->GET(api.events, std::nullopt);
    if (res.result.value() != boost::beast::errc::success) {
        resp.result = res.result;
        return resp;
    }
    string res_body;
//    error_code ec;
    if (res.response) {
        if (res.response->status.code == 200) {
            res_body = res.response->response_body;
        }
    }
    Events events(res_body);
    resp.body = events._events;
    return resp;
}

Response<bool> EventsConnector::visit(const size_t &event_id, const size_t &user_id) {
    std::cout << event_id << user_id << std::endl;
    return {};
}

Response<optional<Event>> EventsConnector::create_event(const Event &event) {
    PartyTimeApi api;
    unordered_map<string, string> headers;
    headers[api.auth_header] = "admin02022";

//    this->connector->POST(api.create_event, headers);
    return {};
}
