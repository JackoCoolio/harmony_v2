#include "Sprite.h"

#include "glew/include/GL/glew.h"
#include <gl/GL.h>

unsigned int Harmony::Sprite::counter = 0;

Harmony::Sprite::Sprite(float x, float y, float xScale, float yScale, float rotation, unsigned int texture, unsigned int shader)
{
	transform = { x, y, xScale, yScale, rotation };
	this->texture = texture;
	this->shader = shader;

	// gen vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float))); // 0 * 4
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); // 2 * 4

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

	// set id
	id = counter++;

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}