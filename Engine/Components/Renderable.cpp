#pragma once

#include "Buffers/include/VAO.hpp"
#include "Buffers/include/VBO.hpp"

struct Renderable
{
	Renderable(VAO vao, VBO vbo, GLuint vertexCount) : m_vao{ vao }, m_vbo{ vbo }, m_vertexCount{m_vertexCount}{};

	VAO m_vao;
	VBO m_vbo;
	GLuint m_vertexCount;
};