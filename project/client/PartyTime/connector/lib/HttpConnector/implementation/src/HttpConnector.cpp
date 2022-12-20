#include "HttpConnector.hpp"
#include "HttpConnectorErrorCategory.hpp"
#include <iostream>


HttpConnector::HttpConnector(const string &host, const string &port)
    :
    host(host),
    port(std::move(port)),
    resolver(ioc),
    stream(ioc) {}


void HttpConnector::set_host(const string &new_host) {
    host = new_host;
}

void HttpConnector::set_port(const string &new_port) {
    port = new_port;
}

void HttpConnector::resolve_url() {
    url = resolver.resolve(host, port);
}

void HttpConnector::resolve_url(const string &new_host, const string &new_port) {
    set_host(new_host);
    set_port(new_port);
    url = resolver.resolve(new_host, new_port);
}

const string &HttpConnector::get_host() const {
    return host;
}

const string &HttpConnector::get_port() const {
    return port;
}

RequestResult<string>
HttpConnector::GET(const string &target,
                   const optional<unordered_map<name, value>>& headers) {
    resolve_url();
    beast::error_code ec;
    stream.connect(url, ec);
    Deferrer def;
    if (ec == beast::errc::success) {
        defer_close(def);
    } else {
        return {std::nullopt, ec};
    }

    auto req = string_request(target, "GET");

    req.set(http::field::host, host);
    req.set(http::field::user_agent, user_agent);
    if (headers) {
        for (const auto& [key, value]: *headers) {
            req.set(key, value);
        }
    }
    http::write(stream, req, ec);
    if (ec) {
        return {std::nullopt, ec};
    }
    Resp response;
    http::read(stream, buffer, response);
    const unordered_map<name, value> response_headers = [&response]{
        unordered_map<name, value> h;
        for (const auto& header: response.base()) {
            h[string(header.name_string())] = string(header.value());
        }
        return h;
    }();
    const Status status = [&response] {
        Status s;
        s.code = response.result_int();
        s.str = string(response.reason());
        return  s;
    }();

    auto body_str = body_to_str(response.body());
    HTTPResponse<string> res(body_str, response_headers, status);
    return {res, beast::error_code(0, HttpConnectorErrorCategory())};
}

RequestResult<string>
HttpConnector::POST(const string &target, const string &body,
                    const optional<unordered_map<name, value>>& headers) {
    resolve_url();
    beast::error_code ec;
    stream.connect(url, ec);
    Deferrer def;
    if (ec == beast::errc::success) {
        defer_close(def);
    } else {
        return {std::nullopt, ec};
    }
    auto req = string_request(target, "POST");
    req.set("Authorization", "admin02022");
    req.set(http::field::host, host);
    req.set(http::field::user_agent, user_agent);
    if (headers) {
        for (const auto& [key, value]: *headers) {
            req.set(key, value);
        }
    }
    req.body() = body;
    req.prepare_payload();
    http::write(stream, req, ec);

    if (ec) {
        return {std::nullopt, ec};
    }
    Resp response;
    http::read(stream, buffer, response);
    const unordered_map<name, value> response_headers = [&response]{
        unordered_map<name, value> h;
        for (const auto& header: response.base()) {
            h[string(header.name_string())] = string(header.value());
        }
        return h;
    }();
    const Status status = [&response] {
        Status s;
        s.code = response.result_int();
        s.str = string(response.reason());
        return  s;
    }();
    auto body_str = body_to_str(response.body());
    HTTPResponse<string> res(body_str, response_headers, status);
    return {res, beast::error_code(0, HttpConnectorErrorCategory())};
}

void HttpConnector::defer_close(Deferrer &def) {
    def.append([ &st = stream ]() {
        beast::error_code ec;
        st.socket().shutdown(tcp::socket::shutdown_both, ec);
        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};
    });
}

str_request HttpConnector::string_request(const string &target, const string &method) const {
    return http::request<http::string_body>{http::string_to_verb(method), target, version};
}

string HttpConnector::body_to_str(const beast::multi_buffer &buffers) {
    return beast::buffers_to_string(buffers.data());
}


