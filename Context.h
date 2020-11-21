#pragma once

#include "Core.h"
#include <string>

struct GLFWwindow;

HARMONY_START

namespace Context
{
	extern GLFWwindow* window;

	// hide width and height so they can't be manually changed
	namespace
	{
		int width;
		int height;
		int shouldClose;
	}

	int initialize(int width, int height, std::string title);
	int getWidth();
	int getHeight();
	void closeApplication();
	int applicationShouldClose();
};

HARMONY_END
