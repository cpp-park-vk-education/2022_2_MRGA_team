#ifndef CONNECTOR_USERS_CONNECTOR_HPP
#define CONNECTOR_USERS_CONNECTOR_HPP
#include "IUsersConnector.hpp"
#include "ILocalStorage.hpp"
#include "IHttpConnector.hpp"
#include <memory>

namespace {
    using std::shared_ptr;
}
// @реализация IUsersConnector
class UsersConnector: public IUsersConnector {

    shared_ptr<ILocalStorage> store;
    shared_ptr<IHttpConnector> connector;
public:
    UsersConnector(shared_ptr<ILocalStorage>& store,
                   shared_ptr<IHttpConnector>& connector);

    Response<User> profile(const size_t& id) override;

    Response<bool> setting(const User& user) override;

    virtual ~UsersConnector() override = default;

};


#endif //CONNECTOR_USERS_CONNECTOR_HPP
