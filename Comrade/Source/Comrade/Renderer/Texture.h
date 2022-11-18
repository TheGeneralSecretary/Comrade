#pragma once

#include <string>

namespace Comrade
{
	class Texture2D
	{
	public:
		Texture2D(int width, int height, int channels);
		Texture2D(const std::string& filepath, bool flipVertically = true);
		~Texture2D();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline unsigned int GetID() const { return m_TextureID; }
		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		void SetBuffer(const void* data);

		inline bool operator==(const Texture2D& rhs) const { return m_TextureID == rhs.GetID(); }

	private:
		unsigned int m_TextureID;
		int m_Width, m_Height, m_Channels;
		unsigned int m_InternalFormat, m_Format;
	};
}
