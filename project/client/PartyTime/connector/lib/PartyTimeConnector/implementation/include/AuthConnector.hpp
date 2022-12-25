#ifndef CONNECTOR_AUTH_CONNECTOR_HPP
#define CONNECTOR_AUTH_CONNECTOR_HPP
#include "IAuthConnector.hpp"
#include "ILocalStorage.hpp"
#include "IHttpConnector.hpp"
#include "api.h"
#include <memory>

namespace {
    using std::shared_ptr;
}

// @реализация IAuthConnector
class AuthConnector: public IAuthConnector {
    PartyTimeApi api;
    shared_ptr<ILocalStorage> store;
    shared_ptr<IHttpConnector> connector;
public:


    AuthConnector(  shared_ptr<ILocalStorage>& store,
                    shared_ptr<IHttpConnector>& connector);

    Response<bool> login(const User& user) override;

    Response<bool> signup(const User& user) override;

    Response<bool> logout() override;

    ~AuthConnector() override = default;

private:
    Response<bool> login_or_signup(const User& user, const string& target, int ec_on_400);

};


#endif //CONNECTOR_AUTH_CONNECTOR_HPP
