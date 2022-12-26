#include "AuthConnector.hpp"

AuthConnector::AuthConnector
    (shared_ptr<ILocalStorage> &store, shared_ptr<IHttpConnector> &connector):store(store), connector(connector) {}

Response<bool> AuthConnector::login(const string &login, const string &password) {
    std::cout << login << password << std::endl;
    return {};
}

Response<bool> AuthConnector::signup(const string &login, const string &password) {
    std::cout << login << password << std::endl;
    return {};
}

Response<bool> AuthConnector::logout() {
    return {};
}
