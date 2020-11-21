#include "Context.h"
#include "Logging.h"

#include <gl/GL.h>
#include "glew/include/GL/glew.h"
#include "glfw3/include/GLFW/glfw3.h"

GLFWwindow* Harmony::Context::window = nullptr;

int Harmony::Context::initialize(int width, int height, std::string title)
{
	glfwInit();

	window = glfwCreateWindow(width, height, title.c_str(), 0, 0);
	Harmony::Context::width = width;
	Harmony::Context::height = height;

	if (!window)
	{
		HarmonyError("Couldn't create a GLFWwindow!");

		return 1;
	}

	glfwMakeContextCurrent(window);
	 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		HarmonyError("Couldn't initialize GLEW!");

		return 1;
	}

	Logging::initialize();

	shouldClose = 0;

	return 0;
}

int Harmony::Context::getWidth()
{
	return width;
}

int Harmony::Context::getHeight()
{
	return height;
}

void Harmony::Context::closeApplication()
{
	shouldClose = 1;
}

int Harmony::Context::applicationShouldClose()
{
	return shouldClose;
}
