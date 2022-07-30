#pragma once

#include "Comrade/Utils/Memory.h"
#include "Comrade/Renderer/VertexBuffer.h"
#include "Comrade/Renderer/IndexBuffer.h"

#include <vector>

namespace Comrade
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const MemoryRef<VertexBuffer>& vb);
		void SetIndexBuffer(const MemoryRef<IndexBuffer>& ib);

		inline const std::vector<MemoryRef<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		inline const MemoryRef<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		unsigned int m_ArrayID;
		std::vector<MemoryRef<VertexBuffer>> m_VertexBuffers;
		MemoryRef<IndexBuffer> m_IndexBuffer;
	};
}
