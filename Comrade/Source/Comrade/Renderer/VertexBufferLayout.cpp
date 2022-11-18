#include "comradepch.h"
#include "Comrade/Renderer/VertexBufferLayout.h"

#include <glad/glad.h>

namespace Comrade
{
	unsigned int GetSizeofShaderDataType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
			return sizeof(GLboolean);
		case ShaderDataType::Int:
			return sizeof(GLint);
		case ShaderDataType::UInt:
			return sizeof(GLuint);
		case ShaderDataType::Float:
			return sizeof(GLfloat);
		case ShaderDataType::Double:
			return sizeof(GLdouble);
		default:
			break;
		}

		return 0;
	}

	unsigned int ConvertShaderDataTypeToGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
			return GL_BOOL;
		case ShaderDataType::Int:
			return GL_INT;
		case ShaderDataType::UInt:
			return GL_UNSIGNED_INT;
		case ShaderDataType::Float:
			return GL_FLOAT;
		case ShaderDataType::Double:
			return GL_DOUBLE;
		default:
			break;
		}

		return 0;
	}

	void VertexBufferLayout::CalculateOffsets()
	{
		unsigned int offset = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size * GetSizeofShaderDataType(element.Type);
			m_Stride += element.Size * GetSizeofShaderDataType(element.Type);
		}
	}
}
