#pragma once

#include <string>

struct MyStruct {
    std::string strl;
    std::string strr;
    MyStruct (std::string& l, std::string& r): strl(l), strr(r) {};
};

std::string my_func();
