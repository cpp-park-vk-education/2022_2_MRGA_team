#include "connector.h"
#include <iostream>

using connector = http_request_connector;

Response<bool> connector::authorization(const string &login,
                                        const string &password) {
    std::cout << login << password;
    // send a get request
    return {true, error_code::success};
}

Response<bool> connector::registration(const string &login,
                                       const string &password) {
    std::cout << login << password;
    return {true, error_code::success};
}

int test_func(int a, int b) {
    return a + b;
}