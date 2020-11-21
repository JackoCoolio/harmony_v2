#include "Texture.h"

#include "Logging.h"

#include "glew/include/GL/glew.h"
#include <gl/GL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

/*
* Returns HARMONY_OK if the texture was loaded successfully.
* @param texture - the unsigned int that will be set with the texture ID
* @param path - the path of the image
* @param alpha - whether or not the image has an alpha channel
* @return Harmony error code
*/
int Harmony::Texture::load(unsigned int& texture, std::string path, int alpha)
{
	stbi_set_flip_vertically_on_load(1);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
	{
		HarmonyWarn("A texture wasn't able to be loaded! [" << path << "]");
		return Harmony::Error::LOAD_FAILURE;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, alpha ? GL_RGBA : GL_RGB, width, height, 0, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	return Harmony::OK;
}
