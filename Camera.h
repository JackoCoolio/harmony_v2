#pragma once

#include "Core.h"

#include "Transform.h"

struct lua_State;

HARMONY_START

namespace Camera
{

	namespace
	{
		Transform transform;
	}

	void registerLuaFunctions(lua_State* L);
	void setPosition(Transform transform);
	Transform& getTransform();

};

HARMONY_END
