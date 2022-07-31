#pragma once

#include "Comrade/Renderer/Renderer2D.h"
#include "Comrade/Utils/Memory.h"

namespace Comrade
{
	class Renderer
	{
	public:
		bool Init();
		void SetViewPort(int width, int height);

		inline MemoryRef<Renderer2D>& GetRenderer2D() { return m_Renderer2D; }

	private:
		MemoryRef<Renderer2D> m_Renderer2D;
	};
}

