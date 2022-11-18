#pragma once

#include "Comrade/Utils/Memory.h"
#include "Comrade/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Comrade
{
	class Render
	{
	public:
		static void Clear();
		static void SetClearColor(const glm::vec4& color);
		static void DrawIndexed(const MemoryRef<VertexArray>& va, unsigned int count = 0);
	};
}
