#include "comradepch.h"
#include "Comrade/Renderer/Renderer.h"
#include "Comrade/Renderer/Render.h"
#include "Comrade/Core/Logger.h"

namespace Comrade
{
	bool Renderer::m_Initialzed = false;
	MemoryRef<Renderer2D> Renderer::m_Renderer2D = nullptr;

	bool Renderer::Init()
	{
		m_Renderer2D = CreateRef<Renderer2D>();
		if (!m_Renderer2D->Init())
		{
			COMRADE_LOG_ERROR("FAILED TO INIT Renderer2D");
			return false;
		}

		return m_Initialzed = true;
	}

	void Renderer::Destroy()
	{
		if (m_Initialzed)
		{
			m_Renderer2D->Destroy();
			m_Initialzed = false;
		}
	}

	void Renderer::SetViewPort(int width, int height)
	{
		Render::SetViewPort(0, 0, width, height);
	}
}
