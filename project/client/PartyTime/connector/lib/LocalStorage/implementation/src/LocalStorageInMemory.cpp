
#include "LocalStorageInMemory.hpp"

optional<string> LocalStorageInMemory::get(const string &key) {
    auto res = store.contains(key);
    if (res) {
        return store[key];
    }
    return std::nullopt;
}

void LocalStorageInMemory::set(const string &key, const string &value) {
    store[key] = value;
}
