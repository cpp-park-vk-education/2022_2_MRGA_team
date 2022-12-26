#include "PartyTimeConnector.hpp"
#include "LocalStorageInMemory.hpp"
#include "HttpConnector.hpp"
#include "AuthConnector.hpp"
#include "UsersConnector.hpp"
#include "EventsConnector.hpp"
#include <memory>

using std::shared_ptr;

PartyTimeConnector::PartyTimeConnector(std::shared_ptr<IAuthConnector>& auth,
                                        std::shared_ptr<IEventsConnector>& events,
                                        std::shared_ptr<IUsersConnector>& users,
                                        shared_ptr<ILocalStorage>& store,
                                        shared_ptr<IHttpConnector>& connector)
: auth(auth), events(events), users(users), store(store), connector(connector) {}

shared_ptr<PartyTimeConnector> PartyTimeConnector::default_implementation(const string& host = "0.0.0.0", const string& port = "8080") {
    static shared_ptr<IHttpConnector> connect = std::make_shared<HttpConnector>(host, port);

    static shared_ptr<ILocalStorage> store = std::make_shared<LocalStorageInMemory>();

    static shared_ptr<IAuthConnector> auth = std::make_shared<AuthConnector>(store, connect);
    static shared_ptr<IUsersConnector> users = std::make_shared<UsersConnector>(store, connect);
    static shared_ptr<IEventsConnector> events = std::make_shared<EventsConnector>(store, connect);

    static shared_ptr<PartyTimeConnector> partyTimeConnector = std::make_shared<PartyTimeConnector>(auth, events, users, store, connect);

    return partyTimeConnector;

}
