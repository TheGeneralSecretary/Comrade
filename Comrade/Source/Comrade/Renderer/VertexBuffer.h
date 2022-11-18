#pragma once

#include "VertexBufferLayout.h"

namespace Comrade
{
	class VertexBuffer
	{
	public:
		VertexBuffer(unsigned int size, unsigned int usage);
		VertexBuffer(const void* data, unsigned int size, unsigned int usage);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
		void SetBuffer(const void* data, unsigned int size);

		inline const VertexBufferLayout& GetLayout() const { return m_Layout; }
		inline void SetLayout(const VertexBufferLayout& layout) { m_Layout = layout; }

	private:
		unsigned int m_BufferID;
		VertexBufferLayout m_Layout;
	};
}
