#include "comradepch.h"

#include <Comrade/Core/Application.h>
#include <Comrade/Core/Logger.h>
#include <Comrade/Renderer/Renderer.h>
#include <Comrade/Renderer/Render.h>
#include <Comrade/Utils/Memory.h>
#include <Comrade/Scene/Scene.h>
#include <Comrade/Entity/Entity.h>
#include <Comrade/Entity/Components.h>
#include <Comrade/Input/Input.h>
#include <Comrade/Renderer/Framebuffer.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

class Sandbox : public Comrade::Application
{
public:
	Sandbox(const Comrade::ApplicationProps& props)
		: Comrade::Application(props)
	{
		m_ActiveScene = Comrade::CreateRef<Comrade::Scene>();

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
		auto& cc = m_CameraEntity.AddComponent<Comrade::CameraComponent>();
		cc.Primary = true;
		cc.Camera.SetOrthographic(10.0f, -1.0f, 1.0f);
		cc.Camera.SetViewPort(props.Width, props.Height);

		m_SquareEntity = m_ActiveScene->CreateEntity("Square");
		m_SquareEntity.GetComponent<Comrade::TransformComponent>().Scale = { 2.0f, 2.0f, 1.0f };
		m_SquareEntity.AddComponent<Comrade::SpriteRendererComponent>(glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f });

		m_Framebuffer = Comrade::CreateRef<Comrade::Framebuffer>(props.Width, props.Height);
	}

	~Sandbox()
	{
	}

	virtual void OnUpdate(Comrade::DeltaTime dt) override
	{
		if (m_ViewPort.x > 0.0f && m_ViewPort.y > 0.0f && (m_Framebuffer->GetWidth() != m_ViewPort.x || m_Framebuffer->GetHeight() != m_ViewPort.y))
		{
			m_Framebuffer->Resize(m_ViewPort.x, m_ViewPort.y);
			m_ActiveScene->OnSceneViewPortResize(m_ViewPort.x, m_ViewPort.y);
		}

		m_FPS = (1.0f / dt);

		m_Framebuffer->Bind();

		Comrade::Renderer::GetRenderer2D()->ResetRenderStats();

		Comrade::Render::SetClearColor({ 0.3f, 0.3f, 0.3f, 0.3f });
		Comrade::Render::Clear();

		m_ActiveScene->OnSceneUpdate(dt);
	
		m_Framebuffer->Unbind();
	}

	virtual void OnEvent(Comrade::Event& event) override
	{
		//COMRADE_LOG_INFO("RECV EVENT:({}, {})", (int)event.GetEventType(), event.IsHandled());
	}

	virtual void OnImGuiRender(Comrade::DeltaTime dt) override
	{
		ImGui::Begin("ViewPort");
		ImVec2 viewport = ImGui::GetContentRegionAvail();
		m_ViewPort = { viewport.x, viewport.y };
		ImGui::Image((void*)m_Framebuffer->GetColorTextureID(), { m_ViewPort.x, m_ViewPort.y }, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();

		auto& stats = Comrade::Renderer::GetRenderer2D()->GetRenderStats();
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
	double m_FPS = 0.0f;
	Comrade::MemoryRef<Comrade::Scene> m_ActiveScene;
	Comrade::Entity m_CameraEntity, m_SquareEntity;
	Comrade::MemoryRef<Comrade::Framebuffer> m_Framebuffer;
	glm::vec2 m_ViewPort;
};

int main(int argc, char** argv)
{
	Comrade::Logger::Init();

	Sandbox* sandbox = new Sandbox({ "Sandbox", 640, 480, true });
	sandbox->Run();
	delete sandbox;
	return 0;
}
