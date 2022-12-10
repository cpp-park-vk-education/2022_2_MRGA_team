#ifndef CONNECTOR_LOCALSTORAGEINMEMORY_HPP
#define CONNECTOR_LOCALSTORAGEINMEMORY_HPP
#include "ILocalStorage.hpp"

#include <unordered_map>

namespace {
    using std::unordered_map;
    using key = string;
    using value = string;
}

class LocalStorageInMemory : public ILocalStorage{
private:
    unordered_map<key, value> store;
public:
    virtual optional<string> get(const string& key) override;
    virtual void set(const string& key, const string& value) override;
};


#endif //CONNECTOR_LOCALSTORAGEINMEMORY_HPP
