#pragma once

#include <glad/glad.h>


// Handles OpenGL texture calls
class Texture
{
public:
	// Generates texture.
	// @param imagePath: File location of image.
	Texture(const char* imagePath);
	~Texture();

	// Binds the texture.
	void Bind() const;
	// Unbinds the texture.
	void Unbind() const;

	// Returns GL id.
	unsigned int GetID() const { return m_id; }

private:
	unsigned int m_id; // GL id
	int width, height, nrChannels; // Number of colour channels

};

