#pragma once

#include <glad/glad.h>


// Handles OpenGL texture calls
class Texture
{
public:
	Texture(const char* imagePath);
	~Texture();

	void Bind() const;
	void Unbind() const;

	unsigned int GetID() const { return m_id; }

private:
	unsigned int m_id;
	int width, height, nrChannels;

};

