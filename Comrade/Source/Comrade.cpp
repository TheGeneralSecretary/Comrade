#include "comradepch.h"

#include <Comrade/Core/Application.h>
#include <Comrade/Core/Logger.h>
#include <Comrade/Renderer/Renderer.h>
#include <Comrade/Renderer/Render.h>
#include <Comrade/Utils/Memory.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

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
		m_FPS = (1.0f / dt);

		m_Renderer->GetRenderer2D()->ResetRenderStats();

		Comrade::Render::SetClearColor({ 0.3f, 0.3f, 0.3f, 0.3f });
		Comrade::Render::Clear();

		m_Renderer->GetRenderer2D()->BeginRender();

		m_Renderer->GetRenderer2D()->RenderQuad({ -0.5f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f });
		m_Renderer->GetRenderer2D()->RenderQuad({ 0.5f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, m_Texture2D);

		m_Renderer->GetRenderer2D()->EndRender();
	}

	virtual void OnImGuiRender(Comrade::DeltaTime dt) override
	{
		auto& stats = m_Renderer->GetRenderer2D()->GetRenderStats();
		ImGui::Begin("Stats");
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("DrawCalls: %d", stats.DrawCallCount);
		ImGui::Text("QuadCount: %d", stats.QuadCount);
		ImGui::Text("VertexCount: %d", stats.GetVertexCount());
		ImGui::Text("IndexCount: %d", stats.GetIndexCount());
		ImGui::Text("FPS: %.2f", m_FPS);
		ImGui::End();
	}

private:
	Comrade::MemoryRef<Comrade::Renderer> m_Renderer;
	Comrade::MemoryRef<Comrade::Texture2D> m_Texture2D;
	double m_FPS = 0.0f;
};

int main(int argc, char** argv)
{
	Comrade::Logger::Init();

	Sandbox* sandbox = new Sandbox({ "Sandbox", 640, 480, true });
	sandbox->Run();
	delete sandbox;
	return 0;
}
