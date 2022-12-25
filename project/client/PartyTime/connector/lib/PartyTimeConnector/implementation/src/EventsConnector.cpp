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
    if (res.result.failed()) {
        resp.result = res.result;
        return resp;
    }
    string res_body;
    int response_code = int(res.response->status.code);
    if (response_code == 200) {
        res_body = res.response->response_body;
    } else {
        resp.result = error_code(response_code, PartyTimeConnectorErrorCategory());
        return resp;
    }
    Events events(res_body);
    resp.body = events.events;
    return resp;
}

Response<optional<vector<Event>>> EventsConnector::my_events() {
    return my_or_visiting_events(api.my_events);
}

Response<optional<vector<Event>>> EventsConnector::visiting_events() {
    return my_or_visiting_events(api.visiting_events);
}

future<Response<optional<vector<Event>>>> EventsConnector::events_async() {
    return std::async(&EventsConnector::events, this);
}

Response<optional<Event>> EventsConnector::visit(const size_t &event_id) {
    return visit_or_unvisit(event_id, api.visit_event);
}

Response<optional<Event>> EventsConnector::unvisit(const size_t &event_id) {
    return visit_or_unvisit(event_id, api.unvisit_event);
}

Response<optional<Event>> EventsConnector::create_event(const Event &event) {
    Response<optional<Event>> answer;
    unordered_map<string, string> headers;
    if (DEBUG) {
        store->set(api.auth_header, "admin02022");
    }
    if (!authorized()) {
        answer.result = error_code(int(PartyTimeConnectorErrorCodes::not_authorized), PartyTimeConnectorErrorCategory());
        return answer;
    } else {
        headers[api.auth_header] = auth_token();
    }

    error_code ec;
    auto json_event = event.toJSON(ec);
    if (ec.failed()) {
        answer.result = ec;
        return answer;
    }
    auto request_result = this->connector->POST(api.create_event, json_event, headers);
    if (request_result.result.failed()) {
        answer.result = request_result.result;
        return answer;
    }
    int response_code = int(request_result.response->status.code);
    if (response_code != int(HttpConnectorErrorCodes::ok)) {
        answer.result = error_code(response_code, PartyTimeConnectorErrorCategory());
        return answer;
    }
    string body = request_result.response->response_body;
    Event created_event = Event::fromJSON(body, ec);
    if (ec) {
        answer.result = ec;
        return answer;
    }
    answer.body = created_event;
    return answer;
}

future<Response<optional<Event>>>
EventsConnector::create_event_async(const Event &event) {
    return std::async(&EventsConnector::create_event, this, event);
}

Response<optional<Event>> EventsConnector::update_event(const Event &event) {
    Response<optional<Event>> answer;
    unordered_map<string, string> headers;
    if (DEBUG) {
        store->set(api.auth_header, "admin02022");
    }
    if (!authorized()) {
        answer.result = error_code(int(PartyTimeConnectorErrorCodes::not_authorized), PartyTimeConnectorErrorCategory());
        return answer;
    } else {
        headers[api.auth_header] = auth_token();
    }
    if (std::to_string(event.user_id) != id()) {
        answer.result = error_code(int(PartyTimeConnectorErrorCodes::forbidden), PartyTimeConnectorErrorCategory());
        return answer;
    }
    error_code ec;
    auto json_event = event.toJSON(ec);
    if (ec.failed()) {
        answer.result = ec;
        return answer;
    }
    auto request_result = this->connector->POST(api.update_event, json_event, headers);
    if (request_result.result.failed()) {
        answer.result = request_result.result;
        return answer;
    }
    int response_code = int(request_result.response->status.code);
    if (response_code != int(HttpConnectorErrorCodes::ok)) {
        answer.result = error_code(response_code, PartyTimeConnectorErrorCategory());
        return answer;
    }
    string body = request_result.response->response_body;
    Event updated_event = Event::fromJSON(body, ec);
    if (ec) {
        answer.result = ec;
        return answer;
    }
    answer.body = updated_event;
    return answer;
}

bool EventsConnector::authorized() const {
    return bool(store->get(api.auth_header));
}

string EventsConnector::auth_token() const {
    return *store->get(api.auth_header);
}

string EventsConnector::id() const {
    return *store->get(api.user_id);
}

Response<optional<Event>>
EventsConnector::visit_or_unvisit(const size_t &event_id, const string &target) {
    Response<optional<Event>> answer;
    unordered_map<string, string> headers;
    if (DEBUG) {
        store->set(api.auth_header, "admin02022");
    }
    if (!authorized()) {
        answer.result = error_code(int(PartyTimeConnectorErrorCodes::not_authorized), PartyTimeConnectorErrorCategory());
        return answer;
    } else {
        headers[api.auth_header] = auth_token();
    }
    auto request_result = this->connector->POST(target, std::to_string(event_id), headers);
    if (request_result.result.failed()) {
        answer.result = request_result.result;
        return answer;
    }
    int response_code = int(request_result.response->status.code);
    if (response_code != int(HttpConnectorErrorCodes::ok)) {
        answer.result = error_code(response_code, PartyTimeConnectorErrorCategory());
        return answer;
    }
    error_code ec;
    string body = request_result.response->response_body;
    Event created_event = Event::fromJSON(body, ec);
    if (ec) {
        answer.result = ec;
        return answer;
    }
    answer.body = created_event;
    return answer;
}

Response<optional<vector<Event>>> EventsConnector::my_or_visiting_events(const string& target) {
    Response<optional<vector<Event>>> answer;
    unordered_map<string, string> headers;
    if (DEBUG) {
        store->set(api.auth_header, "admin02022");
    }
    if (!authorized()) {
        answer.result = error_code(int(PartyTimeConnectorErrorCodes::not_authorized), PartyTimeConnectorErrorCategory());
        return answer;
    } else {
        headers[api.auth_header] = auth_token();
    }

    auto res = this->connector->GET(target, std::nullopt);
    if (res.result.value() != boost::beast::errc::success) {
        answer.result = res.result;
        return answer;
    }
    string res_body;
    int response_code = int(res.response->status.code);
    if (response_code == 200) {
        res_body = res.response->response_body;
    } else {
        answer.result = error_code(response_code, PartyTimeConnectorErrorCategory());
        return answer;
    }
    Events events(res_body);
    answer.body = events.events;
    return answer;
}
