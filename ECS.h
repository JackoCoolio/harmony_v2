#pragma once

#define ECS_DEFINED

#include "Core.h"
#include <string>
#include <vector>

struct lua_State;

HARMONY_START

namespace ECS
{

	extern lua_State* L;
	extern std::vector<std::string> loadedInitSystems;
	extern std::vector<std::string> loadedSystems;
	extern std::vector<std::string> loadQueue;
	extern std::string ecsPath;

	int initialize();
	void destroy();
	int loadScene(std::string path);
	void runSystems(int initialize);
};

HARMONY_END
