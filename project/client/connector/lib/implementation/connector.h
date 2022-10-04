#pragma once
#include "IConnector.hpp"
#include "state.h"

namespace {
    using std::string;
};  // namespace


class http_request_connector : public IConnector {
  private:
    state _state;

  public:
    virtual Response<bool> authorization(const string &login,
                                         const string &password) override;
    virtual Response<bool> registration(const string &login,
                                        const string &password) override;
};
