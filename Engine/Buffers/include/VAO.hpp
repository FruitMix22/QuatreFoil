#pragma once

#include <glad/glad.h>
#include <memory>
#include "Buffers/include/VBO.hpp"

class VAO
{
public:

	VAO(const void* data, GLuint size);
	~VAO();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(GLuint index, int size, GLenum type, bool normalised, GLsizei stride, const void* pointer);
	int GetVertexCount() { return m_vertexCount; }

	unsigned int GetID() const { return m_id; }


private:
	unsigned int m_id;
	std::unique_ptr<VBO> m_vbo;
	int m_vertexCount;
};