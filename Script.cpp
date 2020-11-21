#include "Script.h"
#include "Logging.h"

extern "C"
{
#include "lua/include/lua.h"
#include "lua/include/lauxlib.h"
#include "lua/include/lualib.h"
}

int Harmony::Script::runFile(lua_State* L, std::string path)
{
    if (luaL_dofile(L, path.c_str()) != LUA_OK)
    {
        HarmonyError("Couldn't load lua script at '" << path << "'! See error below.");
        printError(L);

        return 1;
    }

    return 0;
}

void Harmony::Script::printError(lua_State* L)
{
    std::string msg = lua_tostring(L, -1);

    HarmonyError(msg);
    lua_pop(L, -1);
}
