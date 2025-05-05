#include "Buffers/include/FBO.hpp"

#include <glad/glad.h>
#include <iostream>

Framebuffer::Framebuffer(unsigned int width, unsigned int height)
	: m_width(width), m_height(height)
{
	CreateFBO();
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteTextures(1, &m_texID);
	glDeleteRenderbuffers(1, &m_RBO);
}

void Framebuffer::CreateFBO()
{
	if (m_FBO)
	{
		glDeleteFramebuffers(1, &m_FBO);
		glDeleteTextures(1, &m_texID);
		glDeleteRenderbuffers(1, &m_RBO);
	}

	// Frame Buffer
	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	// Colour attatchment for frame buffer to render to
	glGenTextures(1, &m_texID);
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texID, 0);

	// TODO : add depth and stencil support

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Framebuffer is not complete donut" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void Framebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Resize(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;

	CreateFBO();
}
