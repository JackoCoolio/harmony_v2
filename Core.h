#pragma once

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "lua/liblua54.a")
#pragma comment(lib, "glfw3/glfw3.lib")
#pragma comment(lib, "glew/lib/Release/x64/glew32s.lib")

#pragma warning( disable : 4244 4099 )

#define HARMONY_START namespace Harmony {
#define HARMONY_END }

HARMONY_START

constexpr int OK = 0;
constexpr int TRUE = 1;
constexpr int FALSE = 0;

namespace Error
{
	constexpr int LOAD_FAILURE = 1;
}

HARMONY_END
