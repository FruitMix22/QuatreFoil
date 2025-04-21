#pragma once

#include <glad/glad.h>
#include <memory>
#include "Buffers/include/VBO.hpp"
#include "Buffers/include/EBO.hpp"

class VAO
{
public:

	template <typename t, size_t n, typename ui, size_t in>
	VAO(const t(&data)[n], const ui(&indices)[in])
	{
		// Gets reference to data, works out size now, then makes VAO
		// HAD TO DO IT THIS WAY, OTHERWISE ID GET SIZE OF POINTER	
		size_t size = sizeof(t) * n;
		size_t indeSize = sizeof(ui) * in;
		m_indicesCount = indeSize;
		CreateVBO(data, size, indices);
	}


	~VAO();

	void Bind() const;
	void Unbind() const;

	void CreateVBO(const void* data, size_t size, const void* indices);
	void AddVertexBuffer(GLuint index, int size, GLenum type, bool normalised, GLsizei stride, const void* pointer);
	int GetVertexCount() { return m_vertexCount; }
	int GetIndicesCount() { return m_indicesCount; }

	unsigned int GetID() const { return m_id; }


	std::unique_ptr<EBO> m_ebo;
	std::unique_ptr<VBO> m_vbo;
private:
	unsigned int m_id;
	size_t m_vertexCount;
	size_t m_indicesCount;
};