#include "connector.h"
#include "deferer.hpp"
#include <iostream>

using Connector = HttpRequestConnector;

//
// HttpRequestConnector::res(Connector::ioc);


Connector::HttpRequestConnector(const string& host, const string& port):host(host), port(port), resolver(ioc), stream(ioc) {

}

str_request Connector::string_request(const string &target, const http::verb& method) const {
    return http::request<http::string_body>{method, target, version};
}



string Connector::body_to_str(beast::multi_buffer const& buffers) {
    return beast::buffers_to_string(buffers.data());
}



void Connector::defer_close(Deferrer& def) {
    def.append([&st = stream](){
        beast::error_code ec;
        st.socket().shutdown(tcp::socket::shutdown_both, ec);
        if(ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};
        });
}

void Connector::test_request() {
    beast::error_code ec;
    resolve_url();
    stream.connect(url, ec);
    Deferrer def;
    if (ec == beast::errc::success) {
        defer_close(def);
    } else {
        return ;
    }
    const auto target = "/admin/login/?next=/admin/";
    str_request req = string_request(target);
    req.set(http::field::host, host);
    req.set(http::field::user_agent, user_agent);
    beast::error_code ecc;
    // beast::errc::success
    http::write(stream, req, ecc);


    response res;


    http::read(stream, buffer, res);
    buffer.clear();


    // std::cout << res << std::endl;
    // std::cout << res.at("status_code") << std::endl;
    // for (auto& key: res) {
    //     std::cout << key.name_string() << " " << key.value() << std::endl;
    // }

    std::cout << res.result_int() << " " << res.result() << " " << res.reason() << std::endl;
    auto body = body_to_str(res.body());

    std::cout << body << std::endl;

    // stream.socket().shutdown(tcp::socket::shutdown_both, ec);
    // auto &s = stream;

}

Response<bool> Connector::authorization(const string &login,
                                        const string &password) {
    std::cout << login << password;
    // send a get request
    return {true, error_code::success};
}

Response<bool> Connector::registration(const string &login,
                                       const string &password) {
    std::cout << login << password;
    return {true, error_code::success};
}

void Connector::set_host(const string& new_host) {
    host = new_host;
}
void Connector::set_port(const string& new_port) {
    port = new_port;
}

void Connector::resolve_url() {
    url = resolver.resolve(host, port);
}

void Connector::resolve_url(const string& host, const string& port) {
    set_host(host);
    set_port(port);
    url = resolver.resolve(host, port);
}

const string& Connector::get_host() const {
    return host;
}
const string& Connector::get_port() const {
    return port;
}