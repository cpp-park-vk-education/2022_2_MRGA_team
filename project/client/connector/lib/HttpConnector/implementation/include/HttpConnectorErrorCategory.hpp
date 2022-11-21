#ifndef CONNECTOR_HTTP_CONNECTOR_ERROR_CATEGORY_HPP
#define CONNECTOR_HTTP_CONNECTOR_ERROR_CATEGORY_HPP
#include <boost/beast/core.hpp>
#include <string>

enum class HttpConnectorErrorCodes {
    success = 0,
    not_success
};
namespace {
    using std::string;
    using ErrC = HttpConnectorErrorCodes;
    using namespace std::string_literals;
}



class HttpConnectorErrorCategory : public boost::system::error_category{
public:
    static constexpr std::string_view error_name = "http connector";
    const char * name() const BOOST_NOEXCEPT override {
            return error_name.data();
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
            default: {
                return "не могу сказать, плохо или хорошо"s;
            }
        }
    }

};


#endif //CONNECTOR_HTTP_CONNECTOR_ERROR_CATEGORY_HPP
