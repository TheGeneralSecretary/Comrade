#include "comradepch.h"
#include "Comrade/Renderer/Render.h"

#include <glad/glad.h>

namespace Comrade
{
	void Render::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Render::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void Render::SetViewPort(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void Render::DrawIndexed(const MemoryRef<VertexArray>& va, unsigned int count)
	{
		glDrawElements(GL_TRIANGLES, count == 0 ? va->GetIndexBuffer()->GetCount() : count, GL_UNSIGNED_INT, nullptr);
	}
}
