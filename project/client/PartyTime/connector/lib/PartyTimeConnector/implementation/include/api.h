#pragma once
#include <string>


namespace {
    using std::string;
};

struct PartyTimeApi {
    // base_url

    /*-----------AUTH_SERVICE URLS-----------*/

    /*принимает ?login={str}&password={str}
    http-method – POST*/
    const string login = "/api/v1/auth/login";

    /*принимает ?token={str}*,
    чтобы получить доступ к удалению токена
    http-method - DELETE*/
    const string logout = "/api/v1/auth/logout";

    /*принимает ?login={str}&password={str}
    http-method - POST*/
    const string signup = "/api/v1/auth/signup";


    /*-----------USERS_SERVICE URLS-----------*/

    /*принимает ?id={int}
    http-method - GET*/
    const string profile = "/api/v1/profile";

    /*принимает ?id={int} и параметры для настройки + токен
    http-method - PUT*/
    const string settings = "/api/v1/profile/setting";



    /*-----------EVENTS_SERVICE URLS-----------*/

    /*принимает опциональные параметры:
    limit={int}, offset={int}, order_field={str}
    order_by={int}, where={key:value}
    http-method - GET
    example: /api/v1/events/?limit=20&offset=5&order_field=id&order_by=DESC&where="creator_id:5"&where=visitor_id=5
    если запрос отправляется без параметров, то возвращаются все возможные ивентs, которые можно вернуть(лимит самого сервера)
    если offset не задан, то он равен=0,
    если order_field не задан, сортировка не производится,
    если where не задан, то отбираются все результаты запроса*/
    const string events = "/api/v1/events";

    /*принимает ?event_id={int}&user_id={int}
    http-method - POST*/
    const string visit_event = "/api/v1/events/visit";
    const string visit_event = "/api/v1/events/unvisit";

    /*принимает запрос через тело запроса.
    http-method - POST*/
    const string create_event = "/api/v1/events/create";

    const string auth_header = "Authorization";
};
/*
 user {
    id = 0,
    email = "admin@admin.ru"
    birth_date = "1970-01-01",
    description = "this user is admin",
    nickname = "admin",
    password = "qwerty"
}

token {
    id = 0,
    token = "admin02022",
    expire_date_time = "2050-01-02 12:00:00",
    user_id = 0
}
 */
