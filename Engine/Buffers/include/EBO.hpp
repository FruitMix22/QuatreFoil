#pragma once

#include <glad/glad.h>

class EBO
{
public:
	EBO(const void* indices, size_t indicesSize);
	~EBO();

	void Bind() const;
	void Unbind() const;

	GLuint GetID() const { return m_id; }

private:
	GLuint m_id;
};