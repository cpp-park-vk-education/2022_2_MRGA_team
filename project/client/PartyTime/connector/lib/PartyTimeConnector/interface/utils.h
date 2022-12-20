#pragma once
#include <string>
#include <unordered_map>
#include <boost/beast/core.hpp>
#include <future>
namespace {
    using std::string;
    using boost::beast::error_code;
    using std::unordered_map;
    using std::future;
};


template <typename T> struct Response {
    T body;
    error_code result;
};
