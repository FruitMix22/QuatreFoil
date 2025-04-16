#include "Buffers/include/VBO.hpp"

VBO::VBO(const void* data, GLuint size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VBO::~VBO() { glDeleteBuffers(1, &m_id); }

void VBO::Bind() const { glBindBuffer( GL_ARRAY_BUFFER, m_id ); }

void VBO::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }