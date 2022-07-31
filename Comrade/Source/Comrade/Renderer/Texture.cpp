#include "comradepch.h"
#include "Comrade/Renderer/Texture.h"
#include "Comrade/Core/Logger.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Comrade
{
	Texture2D::Texture2D(int width, int height, int channels)
		: m_Width(width), m_Height(height), m_Channels(channels), m_InternalFormat(GL_RGBA8), m_Format(GL_RGBA)
	{
		if (m_Channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_Format = GL_RGBA;
		}
		else if (m_Channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_Format = GL_RGB;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	Texture2D::Texture2D(const std::string& filepath, bool flipVertically)
		: m_InternalFormat(GL_RGBA8), m_Format(GL_RGBA)
	{
		stbi_set_flip_vertically_on_load(flipVertically);
		unsigned char* buffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_Channels, 0);
		unsigned int internalFormat = 0, format = 0;

		if (m_Channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_Format = GL_RGBA;
		}
		else if (m_Channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_Format = GL_RGB;
		}
		else
		{
			COMRADE_LOG_INFO("TEXTURE2D ERROR-> WIDTH: {}, HEIGHT: {}, INVALID CHANNELS: {}", m_Width, m_Height, m_Channels);
		}

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_Format, GL_UNSIGNED_BYTE, buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(buffer);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture2D::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::SetBuffer(const void* data)
	{
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_Format, GL_UNSIGNED_BYTE, data);
	}
}
