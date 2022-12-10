#ifndef CONNECTOR_ILOCALSTORAGE_HPP
#define CONNECTOR_ILOCALSTORAGE_HPP
#include <string>
#include <optional>

namespace {
    using std::string;
    using std::optional;
}

class ILocalStorage {

public:
    virtual optional<string> get(const string& key) = 0;
    virtual void set(const string& key, const string& value) = 0;
    virtual ~ILocalStorage() = default;
};

#endif //CONNECTOR_ILOCALSTORAGE_HPP
