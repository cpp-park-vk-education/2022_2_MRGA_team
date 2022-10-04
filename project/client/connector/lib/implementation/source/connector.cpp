#include "connector.h"

using connector = http_request_connector;

Response<bool> connector::authorization(const string &login,
                                        const string &password) {
    http::Request request{"http://localhost/test"};

    // send a get request
    const auto response = request.send("GET");
    return {true, error_code::success};
}

Response<bool> connector::registration(const string &login,
                                       const string &password) {
    return {true, error_code::success};
}