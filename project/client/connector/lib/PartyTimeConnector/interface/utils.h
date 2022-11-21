#pragma once
#include <string>
#include <unordered_map>
#include <boost/beast/core.hpp>

namespace {
    using std::string;
    using boost::beast::error_code;
    using std::unordered_map;
};


template <typename T> struct Response {
    T body;
    error_code result;
};
