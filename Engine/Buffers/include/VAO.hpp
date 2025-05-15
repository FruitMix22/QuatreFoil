#pragma once

#include <glad/glad.h>
#include <memory>
#include "Buffers/include/VBO.hpp"
#include "Buffers/include/EBO.hpp"

// Handles OpenGL calls for VAO
// Initialises VBO & EBO.
class VAO
{
public:
	// Constructor for VAO.
	// @tparam t: Type of vertex data.
	// @tparam n: number of vertices.
	// @tparam ui: Type of index data.
	// @tparam in: number of indices.
	// @param data: Array of vertex data.
	// @param data: Array of index data.
	template <typename t, size_t n, typename ui, size_t in>
	VAO(const t(&data)[n], const ui(&indices)[in])
	{
		// Sets counts of Vertices and Indices.
		m_vertexCount = sizeof(t) * n;
		m_indicesCount = sizeof(ui) * in;
		// Passes data along to make VAO.
		CreateVAO(data, indices);
	}

	/*
		Was done seperately because if the vertices and index are
	    passed through as straight pointers, getting the size of them 
	    only returned the size of a pointer.
	*/


	// Deletes the buffer.
	~VAO();

	// Binds the buffer.
	void Bind() const;
	// Unbinds the buffer.
	void Unbind() const;

	// Generates the arrays and creates a VBO and EBO.
	// @param data: Vertices.
	// @param indices: Indices.
	void CreateVAO(const void* data, const void* indices);

	// Adds the information information to the VertexAttribPointer and enables it.
	// @param index: Position for the data in the vert shader. ie. location = 0.
	// @param size: Size of each vertex, so with x & y = 2.
	// @param type: Data type.
	// @param normalised: Will data need to be normalised? ie. 255 RGB values.
	// @param stride: Space between vertex attributes, x and y = 2.
	// @param offset: Offset of where to start the data. 
	void AddVertexBuffer(GLuint index, int size, GLenum type, bool normalised, GLsizei stride, const void* offset);

	// @returns Size of vertex array.
	int GetVertexCount() { return m_vertexCount; }
	// @returns Size of Indices array.
	int GetIndicesCount() { return m_indicesCount; }

	// @returns ID set by OpenGl.
	unsigned int GetID() const { return m_id; }


	std::unique_ptr<EBO> m_ebo; // EBO that is made from the indices
	std::unique_ptr<VBO> m_vbo; // VBO that is made from the vertex data
private:
	unsigned int m_id; // ID that is set by OpenGL
	size_t m_vertexCount; // vertices in array
	size_t m_indicesCount; // indices in array
};