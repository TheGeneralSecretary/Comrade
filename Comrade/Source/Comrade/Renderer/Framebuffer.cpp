#include "comradepch.h"
#include "Comrade/Renderer/Framebuffer.h"
#include "Comrade/Core/Asserts.h"

#include <glad/glad.h>

namespace Comrade
{
	Framebuffer::Framebuffer(uint32_t width, uint32_t height)
		: m_FrameBufferID(0), m_Width(width), m_Height(height)
	{
		Reset();
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_FrameBufferID);
		glDeleteTextures(1, &m_ColorTextureID);
		glDeleteTextures(1, &m_DepthTextureID);
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Reset()
	{
		if (m_FrameBufferID)
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
			glDeleteTextures(1, &m_ColorTextureID);
			glDeleteTextures(1, &m_DepthTextureID);
		}

		glCreateFramebuffers(1, &m_FrameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorTextureID);
		glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTextureParameteri(m_ColorTextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_ColorTextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTextureID, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthTextureID);
		glBindTexture(GL_TEXTURE_2D, m_DepthTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Width, m_Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthTextureID, 0);

		COMRADE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "glCheckFrameBufferStatus(FrameBuffer FAILED)");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
