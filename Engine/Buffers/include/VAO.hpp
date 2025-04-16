#pragma once

#include <glad/glad.h>

class VAO
{
public:

	VAO();
	~VAO();

	void Bind() const;
	void Unbind() const;

	void LinkAttribute(GLuint index, int size, GLenum type, bool normalised, GLsizei stride, const void* pointer);

	unsigned int GetID() const { return m_id; }


private:
	unsigned int m_id;
};