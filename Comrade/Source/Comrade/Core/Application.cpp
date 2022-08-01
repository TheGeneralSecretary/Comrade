#include "comradepch.h"
#include "Comrade/Core/Application.h"
#include "Comrade/Utils/DateTime.h"
#include "Comrade/Core/Logger.h"
#include "Comrade/Renderer/Renderer.h"

namespace Comrade
{
	Application* Application::s_Instance = nullptr;

	Application::~Application()
	{
		Renderer::Destroy();
	}

	Application::Application(const ApplicationProps& props)
		: m_AppProps(props), m_Running(true), m_Minimized(false)
	{
		s_Instance = this;

		m_Window = std::make_unique<Window>();
		m_Window->Init({ props.Name, props.Width, props.Height, props.VSync });
		m_Window->SetEventCallback(std::bind(&Application::OnBaseEvent, this, std::placeholders::_1));

		Renderer::Init();

		m_ImGui = std::make_unique<CImGui>();
		m_ImGui->Init();
	}

	void Application::Run()
	{
		DeltaTime lastDeltaTime = 0.0f;

		while (m_Running)
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

	void Application::OnBaseEvent(Event& event)
	{
		event.Dispatch<WindowCloseEvent>(event, std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		event.Dispatch<WindowResizeEvent>(event, std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
		
		if(!event.IsHandled())
			OnEvent(event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		if (event.GetWidth() == 0 && event.GetHeight() == 0)
		{
			m_Minimized = true;
			return true;
		}

		m_Minimized = false;
		Comrade::Renderer::SetViewPort(event.GetWidth(), event.GetHeight());

		return false;
	}
}
