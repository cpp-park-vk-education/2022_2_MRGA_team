#ifndef SERVICE_ERROR_CODES
#define SERVICE_ERROR_CODES
#include <boost/beast/core.hpp>
#include <string>
namespace {
    using namespace std::string_literals;
}

enum class service_error_codes {
    success = 0,
    db_side_error = -1
};

using serv_errc = service_error_codes;

class service_error_category_impl: public boost::system::error_category {
    static constexpr std::string_view category_name = "structs_error_category";
    const char * name() const noexcept override {
        return category_name.data();
    }
    std::string message( int ev ) const override {
        serv_errc ec = static_cast<serv_errc>(ev);

        switch (ec) {
        case serv_errc::success: {
            return "все хорошо"s;
        }
        case serv_errc::db_side_error: {
            return "ошибка на стороне базы данных";
        }
        default:
            return "не знаю"s;
        }
    }
};

static boost::system::error_category const& service_error_category() {
    static const service_error_category_impl instance;
    return instance;
}

#endif //  SERVICE_ERROR_CODES