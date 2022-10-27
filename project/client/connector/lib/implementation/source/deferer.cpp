#include "deferer.h"

Deferrer::Deferrer(init_list<deferred_function> functions) {
    for (auto& func: functions) {
        funcs.push_back(func);
    }
}

void Deferrer::append(deferred_function func) {
    funcs.push_back(func);
}
Deferrer::~Deferrer() {
    for (auto& func: funcs) {
        func();
    }
}