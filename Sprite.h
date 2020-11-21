#pragma once

#include "Core.h"
#include "Transform.h"
#include <array>

HARMONY_START

struct Sprite
{

	Transform transform;

	unsigned int texture;
	unsigned int shader;
	unsigned int vbo, vao, ebo;

	unsigned int id; // used for removing sprites

	static unsigned int counter;
	static constexpr std::array<unsigned int, 6> indices = { 0, 2, 3, 0, 1, 2 };
	Sprite(float x, float y, float xScale, float yScale, float rotation, unsigned int texture, unsigned int shader);
};

HARMONY_END
