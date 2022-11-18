#include "comradepch.h"
#include "Comrade/Renderer/Renderer.h"
#include "Comrade/Renderer/Render.h"
#include "Comrade/Core/Logger.h"

namespace Comrade
{
	bool Renderer::Init()
	{
		m_Renderer2D = CreateRef<Renderer2D>();
		if (!m_Renderer2D->Init())
		{
			COMRADE_LOG_ERROR("FAILED TO m_Renderer2D.Init");
			return false;
		}

		return true;
	}

	void Renderer::SetViewPort(int width, int height)
	{
		Render::SetViewPort(0, 0, width, height);
	}
}
