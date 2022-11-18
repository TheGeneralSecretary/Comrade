#pragma once

#include "Comrade/Utils/Memory.h"

namespace Comrade
{
	class Framebuffer
	{
	public:
		Framebuffer(uint32_t width, uint32_t height);
		~Framebuffer();

		void Bind();
		void Unbind();

		inline uint32_t GetID() const { return m_FrameBufferID; }
		inline uint32_t GetColorTextureID() const { return m_ColorTextureID; }
		inline void Resize(uint32_t width, uint32_t height) { m_Width = width; m_Height = height; Reset(); }
		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

	private:
		void Reset();

	private:
		uint32_t m_Width, m_Height;
		uint32_t m_FrameBufferID;
		uint32_t m_ColorTextureID, m_DepthTextureID;
	};
}
