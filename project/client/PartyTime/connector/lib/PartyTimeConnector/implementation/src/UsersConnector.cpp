#include "UsersConnector.hpp"

UsersConnector::UsersConnector
    (shared_ptr<ILocalStorage> &store, shared_ptr<IHttpConnector> &connector): store(store), connector(connector) {}

Response<User> UsersConnector::profile(const size_t &id) {
    return {};
}

Response<bool> UsersConnector::setting(const User &user) {
    return {};
}
