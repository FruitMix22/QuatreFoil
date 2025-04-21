#pragma once

#include <glad/glad.h>

// Handles OpenGL calls for EBO.
class EBO
{
public:
	// Generates buffers and data.
	// @param indices: Indices for the EBO.
	// @param indicesSize: Size of the indices.
	EBO(const void* indices, size_t indicesSize);

	// Deletes the buffer.
	~EBO();

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