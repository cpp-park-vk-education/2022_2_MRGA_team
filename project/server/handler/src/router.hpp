#ifndef PROJECT_ROUTER_HPP
#define PROJECT_ROUTER_HPP

#include <map>
#include <string>
#include <functional>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

#include "service.hpp"

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>


using bsv = boost::string_view;

struct router {
    std::map<bsv, std::function<void(bsv path)>> get_handler;
    std::map<bsv, std::function<void(bsv path)>> post_handler;
    std::map<bsv, std::function<void(bsv path)>> put_handler;
    std::map<bsv, std::function<void(bsv path)>> delete_handler;

private:
    std::shared_ptr<service> service_ = nullptr;

public:
    explicit router(HCKey hcKey, bsv query_params);

    /*
     * в приватном поле Класс Service, у которого есть поля Auth, и т.д. (названия сервисов)
     * у этих полей будет метод, который вызывается вместо функций profile signup и т.д.
     * внутри сервиса есть уникальный шаред на класс DBObject или как-то так
     * и поля класса сервис имеют функции который по параметрам будут писать данные в респонс.
     *
     * Возможно мне не нужно проталкивать респонс, а проталкивать структуру, которая будет формироваться уже
     * внутри сервиса. А внутри метода http connection уже писать эту структуру в качестве тела запроса или
     * таргета
     */
};


#endif //PROJECT_ROUTER_HPP
