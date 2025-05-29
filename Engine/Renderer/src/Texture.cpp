#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "Renderer/include/Texture.hpp"
#include "Core/include/Console.hpp"
#include "stb_image.h"


Texture::Texture(const char* imagePath, bool forceAlpha)
{
	unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (!data)
	{
		Console::Log("Image for texture load failed: " + std::string(stbi_failure_reason()));
	}
	else 
	{
		glGenTextures(1, &m_id);

		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		GLenum format = (forceAlpha || nrChannels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
}

Texture::~Texture() { glDeleteTextures(1, &m_id); }

void Texture::Bind() const { glBindTexture(GL_TEXTURE_2D, m_id); }
void Texture::Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
