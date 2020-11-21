#include "Shader.h"
#include "File.h"
#include "Logging.h"

#include "glew/include/GL/glew.h"
#include <gl/GL.h>

int checkCompileErrors(unsigned int shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*) malloc(length);

		glGetShaderInfoLog(shader, length, &length, message);

		HarmonyWarn("A vertex shader didn't compile!" << std::endl << message);

		free(message);
	}

	return !success;
}

int checkLinkErrors(unsigned int program)
{
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)malloc(length);

		glGetProgramInfoLog(program, length, &length, message);

		HarmonyWarn("A vertex shader didn't compile!" << std::endl << message);

		free(message);
	}

	return !success;
}

unsigned int Harmony::Shader::loadFromFile(std::string vertPath, std::string fragPath)
{
	std::string vertString, fragString;
	unsigned int vertexShader, fragmentShader;

	Harmony::File::readToString(vertPath, vertString);
	Harmony::File::readToString(fragPath, fragString);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertCString = vertString.c_str();
	glShaderSource(vertexShader, 1, &vertCString, NULL);
	glCompileShader(vertexShader);

	if (checkCompileErrors(vertexShader))
		return -1;

	const char* fragCString = fragString.c_str();
	glShaderSource(fragmentShader, 1, &fragCString, NULL);
	glCompileShader(fragmentShader);

	if (checkCompileErrors(fragmentShader))
		return -1;

	unsigned int id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);

	glLinkProgram(id);

	if (checkLinkErrors(id))
		return -1;

	glBindFragDataLocation(id, 0, "outColor");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return id;
}
