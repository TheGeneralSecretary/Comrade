#include "comradepch.h"
#include "Comrade/Core/Application.h"
#include "Comrade/Utils/DateTime.h"

namespace Comrade
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationProps& props)
		: m_AppProps(props)
	{
		s_Instance = this;

		m_Window = std::make_unique<Window>();
		m_Window->Init({ props.Name, props.Width, props.Height, props.VSync });

		m_ImGui = std::make_unique<CImGui>();
		m_ImGui->Init();
	}

	void Application::Run()
	{
		DeltaTime lastDeltaTime = 0.0f;

		while (true)
		{
			DeltaTime time = DateTime::GetTimeSeconds();
			DeltaTime dt = time - lastDeltaTime;
			lastDeltaTime = time;

			if (dt > 0.0f)
			{
				OnUpdate(dt);

				m_ImGui->BeginFrame();
				OnImGuiRender(dt);
				m_ImGui->EngFrame();
			}

			m_Window->Update();
		}
	}
}
