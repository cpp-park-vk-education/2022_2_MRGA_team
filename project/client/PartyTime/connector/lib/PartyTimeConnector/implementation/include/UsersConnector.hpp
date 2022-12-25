#ifndef CONNECTOR_USERS_CONNECTOR_HPP
#define CONNECTOR_USERS_CONNECTOR_HPP
#include "IUsersConnector.hpp"
#include "ILocalStorage.hpp"
#include "IHttpConnector.hpp"
#include "api.h"
#include <memory>

namespace {
    using std::shared_ptr;
}
// @реализация IUsersConnector
class UsersConnector: public IUsersConnector {
    PartyTimeApi api;
    shared_ptr<ILocalStorage> store;
    shared_ptr<IHttpConnector> connector;
public:
    UsersConnector(shared_ptr<ILocalStorage>& store,
                    shared_ptr<IHttpConnector>& connector);

    Response<User> profile() override;

    Response<User> setting(const User& user) override;

    virtual ~UsersConnector() override = default;

private:
    bool authorized() const;
    string auth_token() const;
    string id() const;

};


#endif //CONNECTOR_USERS_CONNECTOR_HPP
