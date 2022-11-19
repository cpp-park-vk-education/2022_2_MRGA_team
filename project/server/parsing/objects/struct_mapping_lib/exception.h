#pragma once

#include <stdexcept>

namespace sm
{

class StructMappingException : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
	using std::runtime_error::operator=;
};

} // sm