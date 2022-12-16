#include "UsersConnector.hpp"

UsersConnector::UsersConnector
    (shared_ptr<ILocalStorage> &store, shared_ptr<IHttpConnector> &connector): store(store), connector(connector) {}

Response<User> UsersConnector::profile(const size_t &id) {
    std::cout << id << std::endl;
    return {};
}

Response<bool> UsersConnector::setting(const User &user) {
    std::cout << user._nickname << std::endl;
    return {};
}
