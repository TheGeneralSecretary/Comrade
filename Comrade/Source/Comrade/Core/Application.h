#pragma once

#include "Comrade/Core/DeltaTime.h"
#include "Comrade/Core/Window.h"

#include <string>
#include <memory>

namespace Comrade
{
	struct ApplicationProps
	{
		std::string Name;
		int Width;
		int Height;
		bool VSync;
	};

	class Application
	{
	public:
		Application(const ApplicationProps& props);
		virtual void OnUpdate(DeltaTime dt) = 0;

		void Run();

	private:
		ApplicationProps m_AppProps;
		std::unique_ptr<Window> m_Window;
	};
}
