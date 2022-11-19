#include "connector.hpp"

Connector::Connector()
    : auth_conn(new AuthorizationConnector), event_conn(new EventConnector) {}

Connector::~Connector() {
  delete auth_conn;
  delete event_conn;
}
