#include "UsersConnector.hpp"
#include "HttpConnectorErrorCategory.hpp"
#include "PartyTimeConnectorErrorCodes.hpp"
#define DEBUG 1

UsersConnector::UsersConnector
    (shared_ptr<ILocalStorage> &store, shared_ptr<IHttpConnector> &connector): store(store), connector(connector) {}

Response<User> UsersConnector::profile() {
    Response<User> answer;
    unordered_map<string, string> headers;
    if (DEBUG && !authorized()) {
        store->set(api.auth_header, "admin02022");
    }
    if (!authorized()) {
        answer.result = error_code(int(PartyTimeConnectorErrorCodes::not_authorized), PartyTimeConnectorErrorCategory());
        return answer;
    } else {
        headers[api.auth_header] = auth_token();
    }

    auto res = this->connector->GET(api.profile, headers);
    if (res.result.failed()) {
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
    User user(res_body);
    answer.body = user;
    return answer;
}

Response<User> UsersConnector::setting(const User &user) {
    Response<User> answer;
    unordered_map<string, string> headers;
    if (DEBUG && !authorized()) {
        store->set(api.auth_header, "admin02022");
    }
    if (!authorized()) {
        answer.result = error_code(int(PartyTimeConnectorErrorCodes::not_authorized), PartyTimeConnectorErrorCategory());
        return answer;
    } else {
        headers[api.auth_header] = auth_token();
    }
    if (std::to_string(user.id) != id()) {
        answer.result = error_code(int(PartyTimeConnectorErrorCodes::forbidden), PartyTimeConnectorErrorCategory());
        return answer;
    }

    error_code ec;
    auto json_user = user.toJSON(ec);
    if (ec.failed()) {
        answer.result = ec;
        return answer;
    }
    auto request_result = this->connector->POST(api.settings, json_user, headers);
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
    User updated_user = User::fromJSON(body, ec);
    if (ec) {
        answer.result = ec;
        return answer;
    }
    answer.body = updated_user;
    return answer;
}


bool UsersConnector::authorized() const {
    return bool(store->get(api.auth_header));
}

string UsersConnector::auth_token() const {
    return *store->get(api.auth_header);
}

string UsersConnector::id() const {
    return *store->get(api.user_id);
}