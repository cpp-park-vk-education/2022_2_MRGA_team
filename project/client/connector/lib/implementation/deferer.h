#pragma once
#include <initializer_list>
#include <functional>
#include <vector>

namespace {
    using deferred_function = std::function<void()>;
    template <typename T>
    using init_list = std::initializer_list<T>;
    using std::vector;
};

class Deferrer {
    private:
    vector<deferred_function> funcs;
    public:
    Deferrer() = default;
    Deferrer(init_list<deferred_function> functions);
    void append(deferred_function func);

    ~Deferrer();
};