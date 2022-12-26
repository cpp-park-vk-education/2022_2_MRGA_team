#ifndef STRUCTS_ERROR_CODES
#define STRUCTS_ERROR_CODES

#include <boost/system.hpp>
#include <string>
namespace {
    using boost::system::error_category;
    using namespace std::string_literals;
};

enum class structs_error_codes {
    success = 0,
    parsing_error = 1,
    empty_title = 2,
    empty_date = 3,
    empty_nickname = 4
};
using structs_ec = structs_error_codes;

class structs_error_category_impl: public error_category {
    static constexpr std::string_view category_name = "structs_error_category";
    const char * name() const noexcept override {
        return category_name.data();
    }
    std::string message( int ev ) const override {
        structs_ec ec = static_cast<structs_ec>(ev);

        switch (ec) {
        case structs_ec::success: {
            return "все хорошо"s;
        }
        case structs_ec::parsing_error: {
            return "Ошибка при парсинге json"s;
        }
        case structs_ec::empty_title: {
            return "Event doesn`t have title"s;
        }
        case structs_ec::empty_date: {
            return "Event doesn`t have date"s;
        }
        case structs_ec::empty_nickname: {
            return "User doesn`t have nickname"s;
        }
        default:
            return "не знаю"s;
        }
    }
    virtual bool failed( int ev ) const noexcept override {
        if (ev == 0) {
            return false;
        }
        return true;
    }
};

static error_category const& structs_error_category() {
    static const structs_error_category_impl instance;
    return instance;
}

#endif  //  STRUCTS_ERROR_CODES