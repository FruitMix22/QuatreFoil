#include "Buffers/include/VAO.hpp"
#include <iostream>

void VAO::CreateVAO(const void* data, const void*  indices) 
{
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);

    m_vbo = std::make_unique<VBO>(data, m_vertexCount);
    m_ebo = std::make_unique<EBO>(indices, m_indicesCount);
}


VAO::~VAO() { glDeleteVertexArrays(1, &m_id); }

void VAO::Bind() const 
{ 
    glBindVertexArray(m_id);
    m_vbo->Bind();
    m_ebo->Bind();
}

void VAO::Unbind() const 
{
    glBindVertexArray(0);
    m_vbo->Unbind();
    m_ebo->Unbind();
}

void VAO::AddVertexBuffer(GLuint index, int size, GLenum type, bool normalised, GLsizei stride, const void* pointer)
{
    Bind();
    m_vbo->Bind();
    m_ebo->Bind();
    glVertexAttribPointer(index, size, type, normalised, stride, pointer);
    glEnableVertexAttribArray(index);
}