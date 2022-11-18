#pragma once

namespace Comrade
{
	class CImGui
	{
	public:
		bool Init();
		void Destroy();

		void BeginFrame();
		void EngFrame();

	private:
		bool m_Initialized = false;
	};
}
