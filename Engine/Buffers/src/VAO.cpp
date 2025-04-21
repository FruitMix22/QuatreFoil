#include "Buffers/include/VAO.hpp"
#include <iostream>

void VAO::CreateVBO(const void* data, size_t size, const void*  indices) 
{
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);

    m_vbo = std::make_unique<VBO>(data, size);
    m_ebo = std::make_unique<EBO>(indices, m_indicesCount);

    m_vertexCount = size / sizeof(float) / 2;
}


VAO::~VAO() { glDeleteVertexArrays(1, &m_id); }

void VAO::Bind() const 
{ 
    glBindVertexArray(m_id);
    m_vbo->Bind();
    m_ebo->Bind();
}

void VAO::Unbind() const { glBindVertexArray(0); }

void VAO::AddVertexBuffer(GLuint index, int size, GLenum type, bool normalised, GLsizei stride, const void* pointer)
{
    Bind();
    m_vbo->Bind();
    m_ebo->Bind();
    glVertexAttribPointer(index, size, type, normalised, stride, pointer);
    glEnableVertexAttribArray(index);
}