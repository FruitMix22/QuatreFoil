#include "Buffers/include/VAO.hpp"

VAO::VAO() { glGenVertexArrays(1, &m_id); }

VAO::~VAO() { glDeleteVertexArrays(1, &m_id); }

void VAO::Bind() const { glBindVertexArray(m_id); }

void VAO::Unbind() const { glBindVertexArray(0); }

void VAO::LinkAttribute(GLuint index, int size, GLenum type, bool normalised, GLsizei stride, const void* pointer)
{
    glVertexAttribPointer(index, size, type, normalised, stride, pointer);
    glEnableVertexAttribArray(index);
}