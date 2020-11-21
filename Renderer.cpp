#include "Renderer.h"
#include "Context.h"
#include "Camera.h"
#include "Logging.h"

#include "glew/include/GL/glew.h"
#include <gl/GL.h>
#include "glfw3/include/GLFW/glfw3.h"

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "glm/glm/gtx/string_cast.hpp"

extern "C"
{
#include "lua/include/lua.h"
#include "lua/include/lauxlib.h"
#include "lua/include/lualib.h"
}

void Harmony::Renderer::initialize()
{
	HarmonyLog("Initializing viewport with [ 0, 0, " << Harmony::Context::getWidth() << ", " << Harmony::Context::getHeight() << " ]");
	glViewport(0, 0, Harmony::Context::getWidth(), Harmony::Context::getHeight());
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	vertices[0] = { -1.0f, 1.0f, 0.0f, 1.0f };
	vertices[1] = { 1.0f, 1.0f, 1.0f, 1.0f };
	vertices[2] = { 1.0f, -1.0f, 1.0f, 0.0f };
	vertices[3] = { -1.0f, -1.0f, 0.0f, 0.0f };

	projection = glm::ortho(-((float)Harmony::Context::getWidth()) / 2, ((float)Harmony::Context::getWidth()) / 2, -((float)Harmony::Context::getHeight()) / 2, ((float)Harmony::Context::getHeight()) / 2, -1.0f, 1.0f);

}

int luaAddSprite(lua_State* L)
{
	// check if layer is an integer
	int layer = luaL_checkinteger(L, 1);
	if (layer < 0 || layer >= Harmony::Renderer::NUM_LAYERS)
	{
		luaL_error(L, "layer must be [ 0, %i, )", Harmony::Renderer::NUM_LAYERS);
	}

	// check if the sprite is a table
	luaL_checktype(L, 2, LUA_TTABLE);
	
	lua_getfield(L, 2, "x");
	float x = luaL_checknumber(L, -1);

	lua_getfield(L, 2, "y");
	float y = luaL_checknumber(L, -1);

	lua_getfield(L, 2, "x_s");
	float xScale = luaL_checknumber(L, -1);

	lua_getfield(L, 2, "y_s");
	float yScale = luaL_checknumber(L, -1);

	lua_getfield(L, 2, "rot");
	float rotation = luaL_checknumber(L, -1);

	Harmony::Renderer::addSprite(layer, Harmony::Sprite(x, y, xScale, yScale, rotation, 0, 0));

	return 0;
}

void Harmony::Renderer::registerLuaFunctions(lua_State* L)
{

}

void Harmony::Renderer::render(GLFWwindow* window)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 10; i++)
	{
		std::vector<Harmony::Sprite>& layer = layers[i];

		for (int j = 0; j < layer.size(); j++)
		{
			Sprite& sprite = layer[j];

			glBindTexture(GL_TEXTURE_2D, sprite.texture);

			glUseProgram(sprite.shader);

			glBindVertexArray(sprite.vao);

			glBindBuffer(GL_ARRAY_BUFFER, sprite.vbo);

			glm::mat4 model(1.0f);
			model = glm::scale(model, glm::vec3(sprite.transform.xScale, sprite.transform.yScale, 1.0f));
			model = glm::rotate(model, sprite.transform.rotation, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(sprite.transform.x, sprite.transform.y, 0.0f));

			Transform& tf = Harmony::Camera::getTransform();
			glm::mat4 view(1.0f);
			view = glm::scale(view,	glm::vec3(tf.xScale, tf.yScale, 1.0f));
			view = glm::rotate(view, tf.rotation, glm::vec3(0.0f, 0.0f, 1.0f));
			view = glm::translate(view, glm::vec3(-tf.x, -tf.y, 0.0f));

			glm::mat4 mvp = projection * view * model;

			glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));

			glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

			glUseProgram(sprite.shader);

		}

	}

	glfwSwapBuffers(window);
}

int Harmony::Renderer::addSprite(int layer, Sprite sprite)
{
	if (layers[layer].size() < MAX_SPRITES_PER_LAYER)
	{
		Harmony::Renderer::layers[layer].push_back(sprite);
		return 0;
	}

	return 1;
}

int Harmony::Renderer::removeSprite(int layerIndex, unsigned int id)
{
	std::vector<Harmony::Sprite>& layer = Harmony::Renderer::layers[layerIndex];

	bool found = 0;
	int i = 0;
	for (; i < layer.size(); i++)
	{
		if (layer[i].id == id)
		{
			found = 1;
			break;
		}
	}

	// remove sprite at that index
	if (found)
	{
		layer.erase(layer.begin() + i);
		return 0;
	}

	return 1;
}


