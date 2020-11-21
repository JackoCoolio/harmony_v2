#pragma once

#include "Core.h"

#include "glew/include/GL/glew.h"
#include <gl/GL.h>

#include <iostream>
#include <cassert>

#if defined(HARMONY_DEBUG_VERBOSE)
#define HarmonyLog(x) std::cout << "[Harmony-LOG] " << __FILE__ << "(" << __LINE__ << "): "<<  x << std::endl
#else
#define HarmonyLog(x)
#endif

#if defined(HARMONY_DEBUG_VERBOSE) || defined(HARMONY_DEBUG)
#define HarmonyWarn(x) std::cout << "[Harmony-WARN] " << __FILE__ << "(" << __LINE__ << "): "<<  x << std::endl
#else
#define HarmonyWarn(x)
#endif

#define HarmonyError(x) std::cout << "[Harmony-ERROR] " << __FILE__ << "(" << __LINE__ << "): "<<  x << std::endl

#define HarmonyAssert(x, message) if (!(x)) { HarmonyError(message); assert(0); }

HARMONY_START

namespace Logging
{
    void initialize();
}

HARMONY_END
