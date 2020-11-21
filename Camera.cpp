#include "Camera.h"
#include "Logging.h"

extern "C"
{
#include "lua/include/lua.h"
#include "lua/include/lauxlib.h"
#include "lua/include/lualib.h"
}

int luaSetTransform(lua_State* L)
{
	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);

	float xScale = luaL_checknumber(L, 3);
	float yScale = luaL_checknumber(L, 4);

	float rotation = luaL_checknumber(L, 5);

	Harmony::Camera::setPosition({ x, y, xScale, yScale, rotation });

	return 0;
}

int luaGetTransform(lua_State* L)
{
	Harmony::Transform& transform = Harmony::Camera::getTransform();

	lua_pushnumber(L, transform.x);
	lua_pushnumber(L, transform.y);
	lua_pushnumber(L, transform.xScale);
	lua_pushnumber(L, transform.yScale);
	lua_pushnumber(L, transform.rotation);

	return 5;
}

void Harmony::Camera::registerLuaFunctions(lua_State* L)
{
	lua_register(L, "set_camera_transform", luaSetTransform);
	lua_register(L, "get_camera_transform", luaGetTransform);
}

void Harmony::Camera::setPosition(Transform tf)
{
	transform = tf;
}

Harmony::Transform& Harmony::Camera::getTransform()
{
	return transform;
}
