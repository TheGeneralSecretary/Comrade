#pragma once

#include "Comrade/Core/DeltaTime.h"
#include "Comrade/Core/Window.h"
#include "Comrade/ImGui/CImGui.h"
#include "Comrade/Events/AppEvent.h"
#include "Comrade/Renderer/Renderer.h"

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
		Application(const Application&) = delete;
		void operator=(const Application&) = delete;

		Application(const ApplicationProps& props);
		virtual void OnUpdate(DeltaTime dt) = 0;
		virtual void OnEvent(Event& event) = 0;
		virtual void OnImGuiRender(DeltaTime dt) = 0;

		inline static Application* Get() { return s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void Run();

	private:
		void OnBaseEvent(Event& event);
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

	private:
		static Application* s_Instance;
		bool m_Running, m_Minimized;
		ApplicationProps m_AppProps;
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<CImGui> m_ImGui;

	protected:
		MemoryRef<Renderer> m_Renderer;
	};
}
