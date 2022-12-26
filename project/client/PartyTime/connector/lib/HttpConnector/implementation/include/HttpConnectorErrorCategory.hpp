#ifndef CONNECTOR_HTTP_CONNECTOR_ERROR_CATEGORY_HPP
#define CONNECTOR_HTTP_CONNECTOR_ERROR_CATEGORY_HPP
#include <boost/beast/core.hpp>
#include <string>

enum class HttpConnectorErrorCodes {
    success = 0,
    not_success,
    ok = 200u,
    bad_request = 400u,
    not_authorized = 401u,
    forbidden = 403u
};
namespace {
    using std::string;
    using ErrC = HttpConnectorErrorCodes;
    using namespace std::string_literals;
}



class HttpConnectorErrorCategoryImpl : public boost::system::error_category{
public:
    static constexpr std::string_view error_name = "http connector";
    const char * name() const noexcept override {
            return "http connector";
    }
    std::string message( int ev ) const override {
        HttpConnectorErrorCodes errc = static_cast<ErrC>(ev);

        switch (errc) {
            case ErrC::success: {
                return "все хорошо"s;
            }
            case ErrC::not_success: {
                return "все плохо"s;
            }
            case ErrC::forbidden: {
                return "возможно ваш токен просрочен, недействителен или вам не позволено делать это действие";
            }
            case ErrC::bad_request: {
                return "неправильное тело запроса";
            }
            case ErrC::not_authorized: {
                return "вы не авторизованы";
            }
            default: {
                return "не могу сказать, плохо или хорошо"s;
            }
        }
    }
    virtual bool failed( int ev ) const noexcept override{
        if (ev >= 0) {
            return false;
        }
        return true;
    }
};

[[maybe_unused]]static boost::system::error_category const& HttpConnectorErrorCategory() {
    static const HttpConnectorErrorCategoryImpl instance;
    return instance;
}

#endif //CONNECTOR_HTTP_CONNECTOR_ERROR_CATEGORY_HPP
