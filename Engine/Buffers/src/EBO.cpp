#include "Buffers/include/EBO.hpp"

EBO::EBO(const void* indices, size_t indicesSize)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
}

EBO::~EBO() { glDeleteBuffers(1, &m_id); }

void EBO::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }

void EBO::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }