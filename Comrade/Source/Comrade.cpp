#include "comradepch.h"

#include <Comrade/Core/Application.h>
#include <Comrade/Core/Logger.h>
#include <Comrade/Renderer/Renderer.h>
#include <Comrade/Renderer/Render.h>
#include <Comrade/Utils/Memory.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Sandbox : public Comrade::Application
{
public:
	Sandbox(const Comrade::ApplicationProps& props)
		: Comrade::Application(props)
	{
		m_Renderer = Comrade::CreateRef<Comrade::Renderer>();
		if (!m_Renderer->Init())
			COMRADE_LOG_ERROR("FAILED TO INIT RENDERER");

		m_Texture2D = Comrade::CreateRef<Comrade::Texture2D>("Assets/Textures/Comrade.jpg");
	}

	~Sandbox()
	{
	}

	virtual void OnUpdate(Comrade::DeltaTime dt) override
	{
		//COMRADE_LOG_INFO("FPS {}", (1.0f/dt));

		m_Renderer->GetRenderer2D()->ResetRenderStats();

		Comrade::Render::SetClearColor({ 0.3f, 0.3f, 0.3f, 0.3f });
		Comrade::Render::Clear();

		m_Renderer->GetRenderer2D()->BeginRender();

		m_Renderer->GetRenderer2D()->RenderQuad({ -0.5f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f });
		m_Renderer->GetRenderer2D()->RenderQuad({ 0.5f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, m_Texture2D);

		m_Renderer->GetRenderer2D()->EndRender();

		COMRADE_LOG_INFO("DrawCalls: {}", m_Renderer->GetRenderer2D()->GetRenderStats().DrawCallCount);
		COMRADE_LOG_INFO("QuadCount: {}", m_Renderer->GetRenderer2D()->GetRenderStats().QuadCount);
	}

private:
	Comrade::MemoryRef<Comrade::Renderer> m_Renderer;
	Comrade::MemoryRef<Comrade::Texture2D> m_Texture2D;
};

int main(int argc, char** argv)
{
	Comrade::Logger::Init();

	Sandbox* sandbox = new Sandbox({ "Sandbox", 640, 480, true });
	sandbox->Run();
	delete sandbox;
	return 0;
}
