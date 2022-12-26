#pragma once

#include "exception.hpp"
#include "object.hpp"
#include "member_string.hpp"
#include "mapper.hpp"
#include "options/option_bounds.hpp"
#include "options/option_default.hpp"
#include "options/option_not_empty.hpp"
#include "options/option_required.hpp"

#include <string>
#include <utility>

namespace sm
{

template<
	typename T,
	typename V,
	typename ... U,
	template<typename> typename ... Options>
inline void reg(V T::* ptr, const std::string& name, Options<U>&& ... options)
{
	detail::Object<T>::reg(ptr, name, std::forward<Options<U>>(options)...);
}

} // sm

#define BEGIN_STRUCT(STRUCT_NAME) struct STRUCT_NAME {using Self_Q5w6E7r8 = STRUCT_NAME;

#define MEMBER(TYPE, NAME) TYPE NAME = [] {\
	struct_mapping::reg(&Self_Q5w6E7r8::NAME, #NAME);\
	using MEMBER_TYPE = TYPE;\
	return MEMBER_TYPE{};\
} ();

#define MEMBER_OPTIONS(TYPE, NAME, ...) TYPE NAME = [] {\
	struct_mapping::reg(&Self_Q5w6E7r8::NAME, #NAME, __VA_ARGS__);\
	using MEMBER_TYPE = TYPE;\
	return MEMBER_TYPE{};\
} ();

#define END_STRUCT };