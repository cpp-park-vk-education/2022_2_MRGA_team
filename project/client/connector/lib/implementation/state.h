#pragma once
#include <chrono>
#include <string>

namespace {
    using std::string;
    using date = std::chrono::year_month_day;

};  // namespace
// последнюю сессию сохраняем в файл
struct session_token {
    size_t user_id;
    string token;
    date expire_date;
    bool is_set = false;
    void set_token(size_t user_id, const string &token, const string &date);
};
// логины сохраняем все, чтобы предлагать при входе. Пару логина и пароля
// предлагаем сохранить.
struct user_info {
    string login;
    string password;

    // void set_login(const string &login);
    // void set_password(const string &login);
    // void save_login_to_file();
    // void save_login_and_password_to_file();
};

class state {
  public:
    session_token token;
    user_info user;
};
