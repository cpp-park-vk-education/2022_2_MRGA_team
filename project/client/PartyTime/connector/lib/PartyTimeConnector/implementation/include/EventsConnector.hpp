#ifndef CONNECTOR_EVENTS_CONNECTOR_HPP
#define CONNECTOR_EVENTS_CONNECTOR_HPP
#include "IEventsConnector.hpp"
#include "ILocalStorage.hpp"
#include "IHttpConnector.hpp"
#include "api.h"
#include <memory>
#include <vector>
namespace {
    using std::shared_ptr;
}

// @реализация IEventsConnector
class EventsConnector: public IEventsConnector {

    PartyTimeApi api;
    shared_ptr<ILocalStorage> store;
    shared_ptr<IHttpConnector> connector;
public:
    EventsConnector(shared_ptr<ILocalStorage>& store,
                    shared_ptr<IHttpConnector>& connector);

    Response<optional<vector<Event>>> events() override;
    Response<optional<vector<Event>>> my_events() override;
    Response<optional<vector<Event>>> visiting_events() override;
    future<Response<optional<vector<Event>>>> events_async() override;
    Response<optional<Event>> visit(const size_t& event_id) override;
    Response<optional<Event>> unvisit(const size_t& event_id) override;

    Response<optional<Event>> create_event(const Event& event) override;
    future<Response<optional<Event>>> create_event_async(const Event& event) override;

    Response<optional<Event>> update_event(const Event& event) override;

    ~EventsConnector() override = default;

private:
    bool authorized() const;
    string auth_token() const;
    string id() const;

    Response<optional<Event>> visit_or_unvisit(const size_t& event_id, const string& target);
    Response<optional<vector<Event>>> my_or_visiting_events(const string& target);

};


#endif //CONNECTOR_EVENTS_CONNECTOR_HPP
