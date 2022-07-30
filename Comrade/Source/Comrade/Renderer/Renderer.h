#pragma once

#include "Comrade/Utils/Memory.h"
#include "Comrade/Renderer/Shader.h"
#include "Comrade/Renderer/VertexArray.h"
#include "Comrade/Renderer/VertexBuffer.h"
#include "Comrade/Renderer/IndexBuffer.h"

namespace Comrade
{
	class Renderer
	{
	public:
		Renderer();

		void RenderSample();

	private:
		MemoryRef<Shader> m_Shader;
		MemoryRef<VertexArray> m_VertexArray;
		MemoryRef<VertexBuffer> m_VertexBuffer;
		MemoryRef<IndexBuffer> m_IndexBuffer;
	};
}

