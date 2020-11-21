#pragma once

#include "Core.h"

#include <string>

struct lua_State;

HARMONY_START

namespace Script
{
	int runFile(lua_State* L, std::string path);
	void printError(lua_State* L);
};

HARMONY_END
