#include "deferer.h"

Deferrer::Deferrer(init_list<deferred_function> functions) {
    std::copy(functions.begin(), functions.end(), funcs.begin());
}

void Deferrer::append(deferred_function func) {
    funcs.push_back(func);
}
Deferrer::~Deferrer() {
    for (const auto & func : funcs) {
        func();
    }
}
