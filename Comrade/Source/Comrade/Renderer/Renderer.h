#pragma once

#include "Comrade/Renderer/Renderer2D.h"
#include "Comrade/Utils/Memory.h"

namespace Comrade
{
	class Renderer
	{
	public:
		static bool Init();
		static void Destroy();
		static void SetViewPort(int width, int height);

		static inline MemoryRef<Renderer2D>& GetRenderer2D() { return m_Renderer2D; }

	private:
		static bool m_Initialzed;
		static MemoryRef<Renderer2D> m_Renderer2D;
	};
}

