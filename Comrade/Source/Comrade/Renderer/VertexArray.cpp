#include "comradepch.h"
#include "Comrade/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace Comrade
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_ArrayID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_ArrayID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_ArrayID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const MemoryRef<VertexBuffer>& vb)
	{
		glBindVertexArray(m_ArrayID);
		vb->Bind();

		for (int i = 0; i < vb->GetLayout().GetElements().size(); i++)
		{
			auto& element = vb->GetLayout().GetElements()[i];
			glVertexAttribPointer(i, element.Size, ConvertShaderDataTypeToGLType(element.Type), element.Normalized, vb->GetLayout().GetStride(), (const void*)element.Offset);
			glEnableVertexAttribArray(i);
		}

		m_VertexBuffers.push_back(vb);
	}

	void VertexArray::SetIndexBuffer(const MemoryRef<IndexBuffer>& ib)
	{
		glBindVertexArray(m_ArrayID);
		ib->Bind();
		m_IndexBuffer = ib;
	}
}
