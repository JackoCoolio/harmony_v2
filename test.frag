#version 460 core

in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D sampler;

void main()
{
	FragColor = texture(sampler, texcoord);
	//FragColor = vec4(texcoord.x, texcoord.y, texcoord.y, 1.0);
}