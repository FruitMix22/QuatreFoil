#pragma once

class Framebuffer
{
public:
	Framebuffer(unsigned int width, unsigned int height);
	~Framebuffer();

	void Bind();
	void Unbind();

	void Resize(unsigned int width, unsigned int height);

	unsigned int GetTextureID() const { return m_texID; }

private:
	unsigned int m_FBO = 0;
	unsigned int m_texID = 0;
	unsigned int m_RBO = 0;

	unsigned int m_width;
	unsigned int m_height;

	void CreateFBO();
};