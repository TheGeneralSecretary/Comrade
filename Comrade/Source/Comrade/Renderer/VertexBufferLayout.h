#pragma once

#include <string>
#include <vector>

namespace Comrade
{
	enum class ShaderDataType
	{
		Unknown, Bool, Int, UInt, Float, Double
	};

	unsigned int GetSizeofShaderDataType(ShaderDataType type);
	unsigned int ConvertShaderDataTypeToGLType(ShaderDataType type);

	struct VertexBufferElement
	{
		std::string Name;
		unsigned int Size;
		ShaderDataType Type;
		bool Normalized;
		unsigned int Offset;

		VertexBufferElement(const std::string& name, unsigned int size, ShaderDataType type, bool normalized = false)
			: Name(name), Size(size), Type(type), Normalized(normalized), Offset(0)
		{
		}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout() = default;

		VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements)
			: m_Elements(elements), m_Stride(0)
		{
			CalculateOffsets();
		}

		inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

	private:
		void CalculateOffsets();

	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	};
}
