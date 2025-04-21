#include "Buffers/include/VAO.hpp"
#include <iostream>

VAO::VAO(const void* data) 
{
    glGenVertexArrays(1, &m_id);

    // Work out size automatically
    GLuint size = sizeof(data);
    std::cout << "size of data: " << size << std::endl;
    m_vbo = std::make_unique<VBO>(data, size);
    m_vertexCount = size / sizeof(float) / 2;
}

VAO::~VAO() { glDeleteVertexArrays(1, &m_id); }

void VAO::Bind() const { glBindVertexArray(m_id); }

void VAO::Unbind() const { glBindVertexArray(0); }

void VAO::AddVertexBuffer(GLuint index, int size, GLenum type, bool normalised, GLsizei stride, const void* pointer)
{
    Bind();
    m_vbo->Bind();
    glVertexAttribPointer(index, size, type, normalised, stride, pointer);
    glEnableVertexAttribArray(index);
}