#pragma once

#include <vector>

namespace sm::detail
{

class Reset
{
public:
	using ResetFunction = void(*)();

public:
	static void reg(ResetFunction reset)
	{
		reset_functions.push_back(reset);
	}

	static void reset()
	{
		for (auto& reset_function : reset_functions)
		{
			reset_function();
		}
	}

private:
	static inline std::vector<ResetFunction> reset_functions;
};

} // sm::detail