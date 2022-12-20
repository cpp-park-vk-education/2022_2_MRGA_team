#ifndef CONNECTOR_PARTY_TIME_CONNECTOR_ERROR_CATEGORY_HPP
#define CONNECTOR_PARTY_TIME_CONNECTOR_ERROR_CATEGORY_HPP
#include <boost/beast/core.hpp>
#include <string>

enum class PartyTimeConnectorErrorCodes {
    success = 0,
    not_success,
    bad_request = 400u,
    not_authorized = 401u,
    forbidden = 403u
};
namespace {
    using std::string;
    using PTCErrC = PartyTimeConnectorErrorCodes;
    using namespace std::string_literals;
}



class PartyTimeConnectorErrorCategoryImpl : public boost::system::error_category{
public:
    static constexpr std::string_view error_name = "http connector";
    const char * name() const noexcept override {
            return "http connector";
    }
    std::string message( int ev ) const override {
        PTCErrC errc = static_cast<PTCErrC>(ev);

        switch (errc) {
            case PTCErrC::success: {
                return "все хорошо"s;
            }
            case PTCErrC::not_success: {
                return "все плохо"s;
            }
            case PTCErrC::forbidden: {
                return "возможно ваш токен просрочен, недействителен или вам не позволено делать это действие";
            }
            case PTCErrC::bad_request: {
                return "неправильное тело запроса";
            }
            case PTCErrC::not_authorized: {
                return "вы не авторизованы";
            }
            default: {
                return "не могу сказать, плохо или хорошо"s;
            }
        }
    }
    virtual bool failed( int ev ) const noexcept override{
        if (ev == 0) {
            return false;
        }
        return true;
    }
};

[[maybe_unused]]static boost::system::error_category const& PartyTimeConnectorErrorCategory() {
    static const PartyTimeConnectorErrorCategoryImpl instance;
    return instance;
}

#endif //  CONNECTOR_PARTY_TIME_CONNECTOR_ERROR_CATEGORY_HPP
