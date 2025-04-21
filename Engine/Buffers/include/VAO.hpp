#pragma once

#include <glad/glad.h>
#include <memory>
#include "Buffers/include/VBO.hpp"

class VAO
{
public:

	template <typename t, size_t n>
	VAO(const t(&data)[n]) 
	{
		// Gets reference to data, works out size now, then makes VAO
		// HAD TO DO IT THIS WAY, OTHERWISE ID GET SIZE OF POINTER	
		size_t size = sizeof(t) * n;
		CreateVBO(data, size);
	}


	~VAO();

	void Bind() const;
	void Unbind() const;

	void CreateVBO(const void* data, size_t size);
	void AddVertexBuffer(GLuint index, int size, GLenum type, bool normalised, GLsizei stride, const void* pointer);
	int GetVertexCount() { return m_vertexCount; }

	unsigned int GetID() const { return m_id; }


private:
	unsigned int m_id;
	std::unique_ptr<VBO> m_vbo;
	int m_vertexCount;
};