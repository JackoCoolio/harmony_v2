#pragma once

#include <unordered_map>
#include <stdbool.h>

#include "Core.h"

extern "C"
{
#include "lua/include/lua.h"
#include "lua/include/lauxlib.h"
#include "lua/include/lualib.h"
}

HARMONY_START

namespace Input
{

	void initialize();
	void registerLuaFunctions(lua_State* L);
	void pollEvents();
	extern std::unordered_map<int, int> keyStates;
	extern std::unordered_map<int, int> mouseButtonStates;
	extern double mouseX, mouseY;

};

HARMONY_END
