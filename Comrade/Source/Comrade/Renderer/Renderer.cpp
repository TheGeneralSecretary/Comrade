#include "comradepch.h"
#include "Comrade/Renderer/Renderer.h"
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
}
