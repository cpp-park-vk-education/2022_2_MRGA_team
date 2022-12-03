#include "http_connection.hpp"

#include <boost/url/parse.hpp>
#include <boost/url/src.hpp>


#include "router.hpp"


using namespace boost::urls;


void http_connection::read_request() {
    auto self = shared_from_this();

    http::async_read(
            socket_,
            buffer_,
            request_,
            [self](beast::error_code ec, std::size_t bytes_transferred)
            {
                boost::ignore_unused(bytes_transferred);
                if(!ec)
                    self->process_request();
            });
}

void http_connection::process_request() {
    response_.version(request_.version());
    response_.keep_alive(false);

    boost::url url = parse_origin_form(request_.target()).value();

    try {

        switch (request_.method()) {

            case http::verb::get: {
//            // здесь какая-то логика дальнейшего отправления запроса (до базы), возвращающей код ошибки
//            response_.result(http::status::ok);
//            response_.set(http::field::server, "MRGA");
//            create_response();
                std::make_shared<router>(url.query())->get_handler.at(url.path());
                break;
            }
                /*
                 * отдельную логику, вызываемую в случае ошибки */
            case http::verb::post: {
                std::make_shared<router>(url.query())->post_handler.at(url.path());
                break;
            }

            case http::verb::put: {
                std::make_shared<router>(url.query())->put_handler.at(url.path());
                break;
            }

            case http::verb::delete_: {
                std::make_shared<router>(url.query())->delete_handler.at(url.path());
                break;
            }

            default: {
                response_.result(http::status::bad_request);
                response_.set(http::field::content_type, "");
                beast::ostream(response_.body())
                        << "Invalid request-method '"
                        << std::string(request_.method_string())
                        << "'";
                break;
            }
        }

    } catch (std::out_of_range &ec) {
        response_.result(http::status::not_found);
        response_.set(http::field::content_type, "");
        beast::ostream(response_.body())
                << "File not found\r\n"
                << "Invalid url-path '"
                << std::string(url.path())
                << "'";
    }

    write_response();
}

void http_connection::create_response() {
    /*
     * Посмотреть как работать с http::request и вытянуть auth || profile || events
     *
     * Здесь доп парсинг, на определение сервиса, который далее работает.
     * А здесь просто перечислю все в лоб.
     *
     * Строки заменить на enum (юзать числа через switch)
     *
     */

    // "/auth"
    if (request_.target().empty()) {

    } else if (request_.target() == "/login") {
        response_.set(http::field::content_type, "text/json");
        beast::ostream(response_.body())
                << std::string(request_.target());

    } else if (request_.target() == "/logout") {

    } else if (request_.target() == "/signup") {

    }

    // "/profile"
    else if (request_.target().empty()) {

    } else if (request_.target() == "/settings") {

    }

    // "/events"
    else if (request_.target().empty()) {

    } else if (request_.target() == "/visit") {

    } else if (request_.target() == "/create") {

    } else {
        response_.result(http::status::not_found);
        response_.set(http::field::content_type, "text/json");
        beast::ostream(response_.body()) << "File not found\r\n";
    }
}

void http_connection::write_response() {
    auto self = shared_from_this();

    response_.content_length(response_.body().size());
    response_.body();

    http::async_write(
            socket_,
            response_,
            [self](beast::error_code ec, std::size_t)
            {
                self->socket_.shutdown(tcp::socket::shutdown_send, ec);
                self->deadline_.cancel(ec);
            });
}

void http_connection::check_deadline() {
    auto self = shared_from_this();

    deadline_.async_wait(
            [self](beast::error_code ec)
            {
                if (!ec)
                {
                    self->socket_.close(ec);
                }
            });
}
