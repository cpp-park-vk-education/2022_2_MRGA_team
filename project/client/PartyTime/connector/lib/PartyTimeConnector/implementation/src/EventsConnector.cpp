#include "EventsConnector.hpp"
#include "HttpConnectorErrorCategory.hpp"
#include "PartyTimeConnectorErrorCodes.hpp"
#include "api.h"
#define DEBUG 1

EventsConnector::EventsConnector
    (shared_ptr<ILocalStorage> &store, shared_ptr<IHttpConnector> &connector): store(store), connector(connector) {}

Response<optional<vector<Event>>> EventsConnector::events() {
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
    resp.body = events.events;
    return resp;
}

future<Response<optional<vector<Event>>>> EventsConnector::events_async() {
    return std::async(&EventsConnector::events, this);
}

Response<bool> EventsConnector::visit(const size_t &event_id, const size_t &user_id) {
    std::cout << event_id << user_id << std::endl;
    return {};
}

Response<optional<Event>> EventsConnector::create_event(const Event &event) {
    Response<optional<Event>> response;
    unordered_map<string, string> headers;
    if (DEBUG) {
        store->set(api.auth_header, "admin02022");
    }
    if (!authorized()) {
        response.result = error_code(int(PartyTimeConnectorErrorCodes::not_authorized), PartyTimeConnectorErrorCategory());
        return response;
    } else {
        headers[api.auth_header] = auth_token();
    }

    error_code ec;
    auto json_event = event.toJSON(ec);
    if (ec.failed()) {
        response.result = ec;
        return response;
    }
    auto http_response = this->connector->POST(api.create_event, json_event, headers);
    if (http_response.result.failed()) {
        response.result = http_response.result;
        return response;
    }
    int response_code = int(http_response.response->status.code);
    if (response_code != int(HttpConnectorErrorCodes::ok)) {
        response.result = error_code(response_code, PartyTimeConnectorErrorCategory());
        return response;
    }
    string body = http_response.response->response_body;
    Event created_event = Event::fromJSON(body, ec);
    if (ec) {
        response.result = ec;
        return response;
    }
    response.body = created_event;
    return response;
}

future<Response<optional<Event>>>
EventsConnector::create_event_async(const Event &event) {
    return std::async(&EventsConnector::create_event, this, event);
}

bool EventsConnector::authorized() const {
    return (store->get(api.auth_header) ? true :false);
}

string EventsConnector::auth_token() const {
    return *store->get(api.auth_header);
}
