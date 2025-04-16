#pragma once

#include <glad/glad.h>

class VBO
{
public:
	VBO(const void* data, GLuint size);
	~VBO();

	void Bind() const;
	void Unbind() const;

	GLuint GetID() const { return m_id; }

private:
	GLuint m_id;
};