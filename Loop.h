#pragma once

#include "Core.h"

#include <chrono>

HARMONY_START

namespace Loop
{
	namespace
	{
		std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> last;
		long long fixedTimestep;
	}

	void start();
	float step();
	void setFixedTimestep(long long nanoseconds);
	int timestepPassed();
};

HARMONY_END
