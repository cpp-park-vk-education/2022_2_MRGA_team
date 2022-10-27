#pragma once
#include <string>
#include <boost/beast/core.hpp>

namespace {
    using std::string;
    using boost::beast::error_code;
};



template <typename T> struct Response {
    T body;
    error_code result;
};
