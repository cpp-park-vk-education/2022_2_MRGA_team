#ifndef CONNECTOR_AUTH_CONNECTOR_HPP
#define CONNECTOR_AUTH_CONNECTOR_HPP
#include "IAuthConnector.hpp"
#include "ILocalStorage.hpp"
#include "IHttpConnector.hpp"
#include <memory>

namespace {
    using std::shared_ptr;
}

// @реализация IAuthConnector
class AuthConnector: public IAuthConnector {

    shared_ptr<ILocalStorage> store;
    shared_ptr<IHttpConnector> connector;
public:


    AuthConnector(shared_ptr<ILocalStorage>& store,
                  shared_ptr<IHttpConnector>& connector);
    Response<bool> login(const string &login,
                                 const string &password) override;

    Response<bool> signup(const string &login,
                                  const string &password) override;

    Response<bool> logout() override;

    ~AuthConnector() override = default;



};


#endif //CONNECTOR_AUTH_CONNECTOR_HPP
