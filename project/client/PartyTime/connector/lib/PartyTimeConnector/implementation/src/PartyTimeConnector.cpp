#include "PartyTimeConnector.hpp"

PartyTimeConnector::PartyTimeConnector(std::shared_ptr<IAuthConnector>& auth,
                                       std::shared_ptr<IEventsConnector>& events,
                                       std::shared_ptr<IUsersConnector>& users)
: auth(auth), events(events), users(users) {}