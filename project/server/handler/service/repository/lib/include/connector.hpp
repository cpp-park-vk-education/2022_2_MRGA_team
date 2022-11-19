#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "authorization_connector.hpp"
#include "event_connector.hpp"

class Connector {
 public:
  Connector();

  ~Connector();

  IAuthorizationConnector *auth_conn;
  IEventConnector *event_conn;
};
