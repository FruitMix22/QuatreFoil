#pragma once

// Handles OpenGL calls for framebuffers.
class Framebuffer
{
public:
	// Generates frame buffer.
	// @param width: width of the texture.
	// @param height: height of the texture.
	Framebuffer(unsigned int width, unsigned int height, int binding);
	~Framebuffer();

	// Binds the buffer.
	void Bind() const;
	// Unbinds the buffer.
	void Unbind() const;

	// Resizes the current FBO's resolution.
	// @param width: width of the texture.
	// @param height: height of the texture.
	void Resize(unsigned int width, unsigned int height);

	// Gets the Texture ID of the frame buffer.
	unsigned int GetTextureID() const { return m_texID; }

private:
	unsigned int m_FBO = 0; // frame buffer id
	unsigned int m_texID = 0; // Texture id
	unsigned int m_RBO = 0; // Render buffer id

	unsigned int m_width; // width of the texture
	unsigned int m_height; // height of the texture

	int m_bufferPoint = 0; // Binding point for buffer

	// Deletes previous FBO and creates new one.
	void CreateFBO();
};