#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "Renderer/include/Texture.hpp"
#include "Core/include/Console.hpp"
#include "stb_image.h"


Texture::Texture(const char* imagePath)
{
	unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

	glGenTextures(1, &m_id);

	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (!data)
	{
		Console::Log("Image for texture load failed: " + std::string(stbi_failure_reason()));
	}
	else 
	{
		//Console::Log("Image loaded: " + std::to_string(width) + "x" + std::to_string(height));
		stbi_image_free(data);
	}
}

Texture::~Texture() { glDeleteTextures(1, &m_id); }

void Texture::Bind() const { glBindTexture(GL_TEXTURE_2D, m_id); }
void Texture::Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
