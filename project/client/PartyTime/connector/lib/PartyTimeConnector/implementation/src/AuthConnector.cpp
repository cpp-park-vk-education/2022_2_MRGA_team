#include "AuthConnector.hpp"
#include "HttpConnectorErrorCategory.hpp"
#include "PartyTimeConnectorErrorCodes.hpp"
AuthConnector::AuthConnector
    (shared_ptr<ILocalStorage> &store, shared_ptr<IHttpConnector> &connector):store(store), connector(connector) {}

Response<bool> AuthConnector::login(const User& user) {
    return login_or_signup(user, api.login, int(PartyTimeConnectorErrorCodes::wrong_credentials));
}

Response<bool> AuthConnector::signup(const User& user) {
    return login_or_signup(user, api.signup, int(PartyTimeConnectorErrorCodes::nickname_already_exists));
}

Response<bool> AuthConnector::logout() {
    return {};
}
Response<bool> AuthConnector::login_or_signup(const User& user, const string& target, int ec_on_400) {
    Response<bool> answer;
    error_code ec;
    string body = user.toJSON(ec);
    if (ec.failed()) {
        answer.body = false;
        answer.result = ec;
        return answer;
    }

    auto request_result = connector->POST(target, body, std::nullopt);

    if (request_result.result.failed()) {
        answer.result = request_result.result;
        return answer;
    }

    int response_code = int(request_result.response->status.code);
    if (response_code == 400) {
        answer.result = error_code(ec_on_400, PartyTimeConnectorErrorCategory());
        return answer;
    }
    if (response_code != int(HttpConnectorErrorCodes::ok)) {
        answer.result = error_code(response_code, PartyTimeConnectorErrorCategory());
        return answer;
    }
    string resp_body = request_result.response->response_body;
    Token token(resp_body);
    store->set(api.token, resp_body);
    store->set(api.user_id, std::to_string(token.user_id));
    answer.body = true;

    return answer;
}
