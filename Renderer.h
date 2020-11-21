#pragma once

#include <vector>
#include <array>
#include <string>
#include <stdbool.h>

#include "glew/include/GL/glew.h"
#include "glfw3/include/GLFW/glfw3.h"

#include "glm/glm/glm.hpp"

#include "Core.h"
#include "Sprite.h"

struct lua_State L;

HARMONY_START

namespace Renderer
{
	constexpr int NUM_LAYERS = 10;
	constexpr int MAX_SPRITES_PER_LAYER = 256;

	void initialize();
	void registerLuaFunctions(lua_State* L);
	void render(GLFWwindow* window);
	int addSprite(int layer, Sprite sprite);
	int removeSprite(int layer, unsigned int id);

	struct Vertex
	{
		float x, y;
		float texcoordX;
		float texcoordY;
	};

	// Renderer state stuff
	namespace
	{
		// array of layers that will be rendered in order
		std::array<std::vector<Harmony::Sprite>, NUM_LAYERS> layers;
		std::array<Vertex, 4> vertices;
		unsigned int idCounter = 0;
		glm::mat4 projection; // common projection matrix
		
	}

}

HARMONY_END
