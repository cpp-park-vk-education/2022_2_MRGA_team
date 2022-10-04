#include "connector.h"

using connector = http_request_connector;

Response<bool> connector::authorization(const string &login,
                                        const string &password) {
    return {true, error_code::success};
}

Response<bool> connector::registration(const string &login,
                                       const string &password) {
    return {true, error_code::success};
}