#ifndef CONNECTOR_EVENTS_CONNECTOR_HPP
#define CONNECTOR_EVENTS_CONNECTOR_HPP
#include "IEventsConnector.hpp"
#include "ILocalStorage.hpp"
#include "IHttpConnector.hpp"
#include <memory>

namespace {
    using std::shared_ptr;
}

// @реализация IEventsConnector
class EventsConnector: public IEventsConnector {


    shared_ptr<ILocalStorage> store;
    shared_ptr<IHttpConnector> connector;
public:
    EventsConnector(shared_ptr<ILocalStorage>& store,
                    shared_ptr<IHttpConnector>& connector);

    Response<optional<vector<Event>>> events(optional<QueryParams> = std::nullopt) override;
    Response<bool> visit(const size_t& event_id, const size_t& user_id) override;
    Response<optional<Event>> create_event(const Event& event) override;

    ~EventsConnector() override = default;

};


#endif //CONNECTOR_EVENTS_CONNECTOR_HPP
