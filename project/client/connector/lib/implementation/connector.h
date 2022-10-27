#pragma once

#include <string>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>



#include "IConnector.hpp"
#include "deferer.h"
#include "state.h"

namespace {
    using std::string;
    using namespace std::string_literals;
    namespace beast       = boost::beast;
    namespace http        = beast::http;
    namespace net         = boost::asio;
    using tcp             = net::ip::tcp;
    using response        = http::response<http::dynamic_body>;
    using str_request     = http::request<http::string_body>;
    using resolved_result = net::ip::basic_resolver_results<net::ip::tcp>;

};  // namespace


class HttpRequestConnector : public IConnector {
  private:
    // base data
    string host;
    string port;
    resolved_result url;

    // for network
    net::io_context ioc;
    tcp::resolver resolver;
    beast::tcp_stream stream;
    beast::flat_buffer buffer;
    unsigned int version = 11;
    string user_agent    = "HttpRequestConnectorLibAgent";

    // Метод, возвращающий текстовый запрос beast::http::request
    str_request
    string_request(const string &target,
                   const http::verb &method = http::verb::get) const;
    // функция, которая вызывает лямбду закрятия для соединения в своем
    // деструкторе;
    void defer_close(Deferrer &def);

    // метод конвертирующий массив байт в строку std::string
    static string body_to_str(beast::multi_buffer const &buffers);


    // state _state;

  public:
    // Connector конструктор. Принимает два аргумента: ip-адрес хоста и порт.
    HttpRequestConnector(const string &host, const string &port);

    // задать новый ip-адрес хоста
    virtual void set_host(const string &new_host) override;
    // задать новый порт
    virtual void set_port(const string &new_port) override;
    // при изменении host или порт нужно вызвать этот метод для подключения к
    // серверу.
    virtual void resolve_url() override;
    // при изменении host или порт нужно вызвать этот метод для подключения к
    // серверу.
    virtual void resolve_url(const string &host, const string &port) override;
    // получение хоста подключения
    virtual const string &get_host() const override;
    // получение порта подключения
    virtual const string &get_port() const override;


    virtual Response<bool> authorization(const string &login,
                                         const string &password) override;
    virtual Response<bool> registration(const string &login,
                                        const string &password) override;

    void test_request();
};

