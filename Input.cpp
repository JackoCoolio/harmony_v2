#include "Context.h"
#include "Logging.h"
#include "Input.h"

#include "glfw3/include/GLFW/glfw3.h"

std::unordered_map<int, int> Harmony::Input::keyStates;
std::unordered_map<int, int> Harmony::Input::mouseButtonStates;

double Harmony::Input::mouseX, Harmony::Input::mouseY;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Harmony::Input::keyStates[scancode] = 1;
	}
	else if (action == GLFW_RELEASE)
	{
		Harmony::Input::keyStates[scancode] = -1;
	}
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Harmony::Input::mouseButtonStates[button] = 1;
	}
	else if (action == GLFW_RELEASE)
	{
		Harmony::Input::mouseButtonStates[button] = -1;
	}

	// left = 0
	// right = 1
	// middle = 2
}

void mouseMoveCallback(GLFWwindow* window, double x, double y)
{
	Harmony::Input::mouseX = x;
	Harmony::Input::mouseY = y;
}

void Harmony::Input::initialize()
{
	glfwSetKeyCallback(Harmony::Context::window, keyCallback);
	glfwSetMouseButtonCallback(Harmony::Context::window, mouseButtonCallback);
	glfwSetCursorPosCallback(Harmony::Context::window, mouseMoveCallback);
}

int luaGetMousePosition(lua_State* L)
{
	lua_pushnumber(L, Harmony::Input::mouseX);
	lua_pushnumber(L, Harmony::Input::mouseY);

	return 2;
}

int luaGetClickState(lua_State* L)
{
	int button = luaL_checkinteger(L, 1);

	lua_pushnumber(L, Harmony::Input::mouseButtonStates[button]);

	return 1;
}

int luaGetKeyState(lua_State* L)
{
	int key = luaL_checkinteger(L, 1);

	lua_pushnumber(L, Harmony::Input::keyStates[key]);

	return 1;
}

void addKeyConstant(lua_State* L, std::string name, int key)
{
	HarmonyLog("Adding key [" << name << "] with code " << key);

	// clear stack
	lua_settop(L, 0);

	lua_getglobal(L, "harmony");

	lua_getfield(L, -1, "key");

	lua_pushstring(L, name.c_str());
	lua_pushnumber(L, glfwGetKeyScancode(key));

	lua_settable(L, -3);
}

void setKeyConstants(lua_State* L)
{
	// set all constants
	addKeyConstant(L, "space", GLFW_KEY_SPACE);
	addKeyConstant(L, "apostrophe", GLFW_KEY_APOSTROPHE);
	addKeyConstant(L, "comma", GLFW_KEY_COMMA);
	addKeyConstant(L, "minus", GLFW_KEY_MINUS);
	addKeyConstant(L, "period", GLFW_KEY_PERIOD);
	addKeyConstant(L, "zero", GLFW_KEY_0);
	addKeyConstant(L, "one", GLFW_KEY_1);
	addKeyConstant(L, "two", GLFW_KEY_2);
	addKeyConstant(L, "three", GLFW_KEY_3);
	addKeyConstant(L, "four", GLFW_KEY_4);
	addKeyConstant(L, "five", GLFW_KEY_5);
	addKeyConstant(L, "six", GLFW_KEY_6);
	addKeyConstant(L, "seven", GLFW_KEY_7);
	addKeyConstant(L, "eight", GLFW_KEY_8);
	addKeyConstant(L, "nine", GLFW_KEY_9);
	addKeyConstant(L, "semicolon", GLFW_KEY_SEMICOLON);
	addKeyConstant(L, "equal", GLFW_KEY_EQUAL);
	addKeyConstant(L, "a", GLFW_KEY_A);
	addKeyConstant(L, "b", GLFW_KEY_B);
	addKeyConstant(L, "c", GLFW_KEY_C);
	addKeyConstant(L, "d", GLFW_KEY_D);
	addKeyConstant(L, "e", GLFW_KEY_E);
	addKeyConstant(L, "f", GLFW_KEY_F);
	addKeyConstant(L, "g", GLFW_KEY_G);
	addKeyConstant(L, "h", GLFW_KEY_H);
	addKeyConstant(L, "i", GLFW_KEY_I);
	addKeyConstant(L, "j", GLFW_KEY_J);
	addKeyConstant(L, "k", GLFW_KEY_K);
	addKeyConstant(L, "l", GLFW_KEY_L);
	addKeyConstant(L, "m", GLFW_KEY_M);
	addKeyConstant(L, "n", GLFW_KEY_N);
	addKeyConstant(L, "o", GLFW_KEY_O);
	addKeyConstant(L, "p", GLFW_KEY_P);
	addKeyConstant(L, "q", GLFW_KEY_Q);
	addKeyConstant(L, "r", GLFW_KEY_R);
	addKeyConstant(L, "s", GLFW_KEY_S);
	addKeyConstant(L, "t", GLFW_KEY_T);
	addKeyConstant(L, "u", GLFW_KEY_U);
	addKeyConstant(L, "v", GLFW_KEY_V);
	addKeyConstant(L, "w", GLFW_KEY_W);
	addKeyConstant(L, "x", GLFW_KEY_X);
	addKeyConstant(L, "y", GLFW_KEY_Y);
	addKeyConstant(L, "z", GLFW_KEY_Z);
	addKeyConstant(L, "left_bracket", GLFW_KEY_LEFT_BRACKET);
	addKeyConstant(L, "backslash", GLFW_KEY_BACKSLASH);
	addKeyConstant(L, "right_bracket", GLFW_KEY_RIGHT_BRACKET);
	addKeyConstant(L, "grave_accent", GLFW_KEY_GRAVE_ACCENT);
	addKeyConstant(L, "world_1", GLFW_KEY_WORLD_1);
	addKeyConstant(L, "world_2", GLFW_KEY_WORLD_2);
	addKeyConstant(L, "escape", GLFW_KEY_ESCAPE);
	addKeyConstant(L, "enter", GLFW_KEY_ENTER);
	addKeyConstant(L, "tab", GLFW_KEY_TAB);
	addKeyConstant(L, "backspace", GLFW_KEY_BACKSPACE);
	addKeyConstant(L, "insert", GLFW_KEY_INSERT);
	addKeyConstant(L, "delete", GLFW_KEY_DELETE);
	addKeyConstant(L, "right", GLFW_KEY_RIGHT);
	addKeyConstant(L, "left", GLFW_KEY_LEFT);
	addKeyConstant(L, "down", GLFW_KEY_DOWN);
	addKeyConstant(L, "up", GLFW_KEY_UP);
	addKeyConstant(L, "page_up", GLFW_KEY_PAGE_UP);
	addKeyConstant(L, "page_down", GLFW_KEY_PAGE_DOWN);
	addKeyConstant(L, "home", GLFW_KEY_HOME);
	addKeyConstant(L, "end", GLFW_KEY_END);
	addKeyConstant(L, "caps_lock", GLFW_KEY_CAPS_LOCK);
	addKeyConstant(L, "scroll_lock", GLFW_KEY_SCROLL_LOCK);
	addKeyConstant(L, "num_lock", GLFW_KEY_NUM_LOCK);
	addKeyConstant(L, "print_screen", GLFW_KEY_PRINT_SCREEN);
	addKeyConstant(L, "pause", GLFW_KEY_PAUSE);
	addKeyConstant(L, "f1", GLFW_KEY_F1);
	addKeyConstant(L, "f2", GLFW_KEY_F2);
	addKeyConstant(L, "f3", GLFW_KEY_F3);
	addKeyConstant(L, "f4", GLFW_KEY_F4);
	addKeyConstant(L, "f5", GLFW_KEY_F5);
	addKeyConstant(L, "f6", GLFW_KEY_F6);
	addKeyConstant(L, "f7", GLFW_KEY_F7);
	addKeyConstant(L, "f8", GLFW_KEY_F8);
	addKeyConstant(L, "f9", GLFW_KEY_F9);
	addKeyConstant(L, "f10", GLFW_KEY_F10);
	addKeyConstant(L, "f11", GLFW_KEY_F11);
	addKeyConstant(L, "f12", GLFW_KEY_F12);
	addKeyConstant(L, "f13", GLFW_KEY_F13);
	addKeyConstant(L, "f14", GLFW_KEY_F14);
	addKeyConstant(L, "f15", GLFW_KEY_F15);
	addKeyConstant(L, "f16", GLFW_KEY_F16);
	addKeyConstant(L, "f17", GLFW_KEY_F17);
	addKeyConstant(L, "f18", GLFW_KEY_F18);
	addKeyConstant(L, "f19", GLFW_KEY_F19);
	addKeyConstant(L, "f20", GLFW_KEY_F20);
	addKeyConstant(L, "f21", GLFW_KEY_F21);
	addKeyConstant(L, "f22", GLFW_KEY_F22);
	addKeyConstant(L, "f23", GLFW_KEY_F23);
	addKeyConstant(L, "f24", GLFW_KEY_F24);
	addKeyConstant(L, "f25", GLFW_KEY_F25);
	addKeyConstant(L, "kp_0", GLFW_KEY_KP_0);
	addKeyConstant(L, "kp_1", GLFW_KEY_KP_1);
	addKeyConstant(L, "kp_2", GLFW_KEY_KP_2);
	addKeyConstant(L, "kp_3", GLFW_KEY_KP_3);
	addKeyConstant(L, "kp_4", GLFW_KEY_KP_4);
	addKeyConstant(L, "kp_5", GLFW_KEY_KP_5);
	addKeyConstant(L, "kp_6", GLFW_KEY_KP_6);
	addKeyConstant(L, "kp_7", GLFW_KEY_KP_7);
	addKeyConstant(L, "kp_8", GLFW_KEY_KP_8);
	addKeyConstant(L, "kp_9", GLFW_KEY_KP_9);
	addKeyConstant(L, "kp_decimal", GLFW_KEY_KP_DECIMAL);
	addKeyConstant(L, "kp_divide", GLFW_KEY_KP_DIVIDE);
	addKeyConstant(L, "kp_multiply", GLFW_KEY_KP_MULTIPLY);
	addKeyConstant(L, "kp_subtract", GLFW_KEY_KP_SUBTRACT);
	addKeyConstant(L, "kp_add", GLFW_KEY_KP_ADD);
	addKeyConstant(L, "kp_enter", GLFW_KEY_KP_ENTER);
	addKeyConstant(L, "kp_equal", GLFW_KEY_KP_EQUAL);
	addKeyConstant(L, "left_shift", GLFW_KEY_LEFT_SHIFT);
	addKeyConstant(L, "left_control", GLFW_KEY_LEFT_CONTROL);
	addKeyConstant(L, "left_alt", GLFW_KEY_LEFT_ALT);
	addKeyConstant(L, "left_super", GLFW_KEY_LEFT_SUPER);
	addKeyConstant(L, "right_shift", GLFW_KEY_RIGHT_SHIFT);
	addKeyConstant(L, "right_control", GLFW_KEY_RIGHT_CONTROL);
	addKeyConstant(L, "right_alt", GLFW_KEY_RIGHT_ALT);
	addKeyConstant(L, "right_super", GLFW_KEY_RIGHT_SUPER);
	//addKeyConstant(L, "menu", GLFW_KEY_MENU); // ???

}

void Harmony::Input::registerLuaFunctions(lua_State* L)
{
	lua_register(L, "get_mouse_pos", luaGetMousePosition);
	lua_register(L, "get_click_state", luaGetClickState);
	lua_register(L, "get_key_state", luaGetKeyState);

	// set up key constants
	setKeyConstants(L);
}

void Harmony::Input::pollEvents()
{
	for (auto iter = Harmony::Input::keyStates.begin(); iter != Harmony::Input::keyStates.end(); iter++)
	{
		if (iter->second == -1)
		{
			iter->second = -2;
		}
		else if (iter->second == 1)
		{
			iter->second = 2;
		}
	}

	for (auto iter = Harmony::Input::mouseButtonStates.begin(); iter != Harmony::Input::mouseButtonStates.end(); iter++)
	{
		if (iter->second == -1)
		{
			iter->second = -2;
		}
		else if (iter->second == 1)
		{
			iter->second = 2;
		}
	}

	glfwPollEvents();
}
