#pragma once

namespace Comrade
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const unsigned int* data, unsigned int count, unsigned int usage);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() { return m_Count; }

	private:
		unsigned int m_BufferID;
		unsigned int m_Count;
	};
}
