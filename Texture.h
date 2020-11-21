#pragma once

#include "Core.h"

#include <string>

HARMONY_START

namespace Texture
{
	int load(unsigned int& texture, std::string path, int alpha);
};

HARMONY_END
