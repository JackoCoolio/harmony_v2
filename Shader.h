#pragma once

#include "Core.h"

#include <string>

HARMONY_START

namespace Shader
{
	unsigned int loadFromFile(std::string vertPath, std::string fragPath);
};

HARMONY_END
