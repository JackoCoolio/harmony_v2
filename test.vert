#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexcoord;

out vec2 texcoord;

layout (location = 0) uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(aPos, 0.0f, 1.0f);

	texcoord = aTexcoord;
}