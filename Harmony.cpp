

//#define GLEW_STATIC

#include <iostream>

#include "Core.h"
#include "ECS.h"
#include "Context.h"
#include "Renderer.h"
#include "Shader.h"
#include "Logging.h"
#include "Input.h"
#include "Texture.h"
#include "Camera.h"
#include "Loop.h"

using namespace Harmony;

#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{

	if (Context::initialize(640, 480, "test"))
		return 1;

	Input::initialize();

	Renderer::initialize();
	HarmonyLog("Renderer initialized!");

	unsigned int shader = Shader::loadFromFile("test.vert", "test.frag");
	unsigned int texture;
	if (Texture::load(texture, "assets/heart.png", Harmony::TRUE) != Harmony::OK)
	{
		return 1;
	}
	
	Sprite sprite(0, 0, 20, 20, 0, texture, shader);

	Renderer::addSprite(0, sprite);

	if (ECS::initialize())
		return 1;

	if (ECS::loadScene("assets/scenes/main.lua"))
		return 1;

	ECS::runSystems(1);

	Loop::start();

	do
	{

		//HarmonyLog("Delta: " << Loop::step());

		ECS::runSystems(0);

		Renderer::render(Context::window);

		Input::pollEvents();

	} while (!Context::applicationShouldClose());

	return 0;
}
