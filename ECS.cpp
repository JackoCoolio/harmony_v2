#include "ECS.h"
#include "Script.h"
#include "Logging.h"
#include "Input.h"
#include "Context.h"
#include "Camera.h"

extern "C"
{
#include "lua/include/lua.h"
#include "lua/include/lauxlib.h"
#include "lua/include/lualib.h"
}

#include <iostream>

lua_State* Harmony::ECS::L = nullptr;
std::vector<std::string> Harmony::ECS::loadedSystems;
std::vector<std::string> Harmony::ECS::loadedInitSystems;
std::vector<std::string> Harmony::ECS::loadQueue;
std::string Harmony::ECS::ecsPath;

int luaAddSystem(lua_State* L)
{
	std::string name = luaL_checkstring(L, 1);

	Harmony::ECS::loadedSystems.push_back(name);

	// this returns zero values
	return 0;
}

int luaAddInitSystem(lua_State* L)
{
	std::string name = luaL_checkstring(L, 1);

	Harmony::ECS::loadedInitSystems.push_back(name);

	// this returns zero values
	return 0;
}

int luaLoadScript(lua_State* L)
{
	std::string path = luaL_checkstring(L, 1);

	// add to queue
	Harmony::ECS::loadQueue.push_back(path);

	return 0;
}

int luaCloseApplication(lua_State* L)
{
	Harmony::Context::closeApplication();

	return 0;
}

int Harmony::ECS::initialize()
{
	Harmony::ECS::L = luaL_newstate();

	if (Harmony::ECS::L == nullptr)
		return 1;

	luaL_openlibs(Harmony::ECS::L);

	luaL_dofile(Harmony::ECS::L, "harmony.lua");

	lua_register(L, "add_system", luaAddSystem);
	lua_register(L, "add_init_system", luaAddInitSystem);
	lua_register(L, "load_script", luaLoadScript);
	lua_register(L, "close_application", luaCloseApplication);

	Harmony::Input::registerLuaFunctions(L);
	Harmony::Camera::registerLuaFunctions(L);

	// Lock Harmony table
	luaL_dostring(L, "setmetatable(harmony,{__newindex=function(a,b,c)error(\"Can't change Harmony constants!\")end})");
	return 0;
}

void Harmony::ECS::destroy()
{
	lua_close(Harmony::ECS::L);
}

int Harmony::ECS::loadScene(std::string path)
{

	HarmonyLog("Loading scene from file '" << path << "'");

	// clear the stack, just because
	lua_settop(Harmony::ECS::L, 0);

	HarmonyLog("Setting up scene loading...");

	if (luaL_dofile(Harmony::ECS::L, path.c_str()) != LUA_OK)
	{
		Harmony::Script::printError(Harmony::ECS::L);

		return 1;
	}

	lua_getglobal(Harmony::ECS::L, "scene_data");

	if (!lua_istable(Harmony::ECS::L, -1))
	{
		HarmonyError("Something went wrong! scene_data isn't a table!");

		return 1;
	}

	HarmonyLog("Scene loaded successfully!");

	return 0;
}

int luaGetComponentArrays(lua_State* L)
{
	int numArgs = lua_gettop(L);

	lua_getglobal(L, "scene_data");

	lua_getfield(L, -1, "components");

	// check if scene_data still exists
	if (!lua_istable(L, -1))
	{
		return luaL_error(L, "Couldn't get components, because scene_data.components is not a table!");
	}

	// check if arguments are all strings
	for (int i = 1; i <= numArgs; i++)
		luaL_checkstring(L, i);

	for (int i = 1; i <= numArgs; i++)
	{
		std::string componentName = lua_tostring(L, i);

		lua_getfield(L, -i, componentName.c_str());
	}

	return numArgs;
}

void Harmony::ECS::runSystems(int initialize)
{

	if (loadQueue.size() > 0)
	{
		HarmonyLog("Loading scripts...");

		for (std::string& path : loadQueue)
		{
			luaL_dofile(L, path.c_str());
		}

		loadQueue.clear();
	}

	if (initialize)
		HarmonyLog("Initializing systems...");

	// really odd way of doing this... just make an initialization function i think...
	for (std::string& funcName : (initialize ? Harmony::ECS::loadedInitSystems : Harmony::ECS::loadedSystems))
	{
		lua_getglobal(Harmony::ECS::L, funcName.c_str());

		if (lua_isfunction(Harmony::ECS::L, -1))
		{
			if (lua_pcall(Harmony::ECS::L, 0, 0, 0) != LUA_OK)
			{
				Harmony::Script::printError(Harmony::ECS::L);
			}

			lua_pop(Harmony::ECS::L, -1);
		}
		else
		{
			HarmonyWarn("Couldn't find a function for " << funcName << "!");
		}
	}
}
