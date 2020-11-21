#include "Loop.h"

#include <iostream>

void Harmony::Loop::start()
{
	last = std::chrono::high_resolution_clock::now();
}

float Harmony::Loop::step()
{
	std::chrono::nanoseconds duration = std::chrono::high_resolution_clock::now() - last;

	last = std::chrono::high_resolution_clock::now();

	return ((float)duration.count()) / 1000000;
}

void Harmony::Loop::setFixedTimestep(long long nanoseconds)
{
	fixedTimestep = nanoseconds;
}

int Harmony::Loop::timestepPassed()
{
	return 0;
}
