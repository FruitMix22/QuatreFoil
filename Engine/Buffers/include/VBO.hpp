#pragma once

#include <glad/glad.h>

// Handles OpenGL calls for VBO.
class VBO
{
public:
	// Generates buffers and data.
	// @param data: Vertices for the VBO.
	// @param size: Size of the vertices.
	VBO(const void* data, GLuint size);

	// Deletes the buffer.
	~VBO();

	// Binds the buffer.
	void Bind() const;
	// Unbinds the buffer.
	void Unbind() const;

	// Returns the ID.
	// @returns Gluint ID of the buffer.
	GLuint GetID() const { return m_id; }

private:
	GLuint m_id; // ID set by OpenGL in constructor
};