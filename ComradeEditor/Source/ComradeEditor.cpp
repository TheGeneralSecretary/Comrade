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

namespace Comrade
{
	class ComradeEditor : public Application
	{
	public:
		ComradeEditor(const ApplicationProps& props)
			: Application(props)
		{
			m_ActiveScene = CreateRef<Scene>();

			m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
			auto& cc = m_CameraEntity.AddComponent<CameraComponent>();
			cc.Primary = true;
			cc.Camera.SetOrthographic(10.0f, -1.0f, 1.0f);
			cc.Camera.SetViewPort(props.Width, props.Height);

			m_SquareEntity = m_ActiveScene->CreateEntity("Square");
			m_SquareEntity.GetComponent<TransformComponent>().Scale = { 2.0f, 2.0f, 1.0f };
			m_SquareEntity.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f });

			m_Framebuffer = CreateRef<Framebuffer>(props.Width, props.Height);
		}

		~ComradeEditor()
		{
		}

		virtual void OnUpdate(DeltaTime dt) override
		{
			if (m_ViewPort.x > 0.0f && m_ViewPort.y > 0.0f && (m_Framebuffer->GetWidth() != m_ViewPort.x || m_Framebuffer->GetHeight() != m_ViewPort.y))
			{
				m_Framebuffer->Resize(m_ViewPort.x, m_ViewPort.y);
				m_ActiveScene->OnSceneViewPortResize(m_ViewPort.x, m_ViewPort.y);
			}

			m_FPS = (1.0f / dt);

			m_Framebuffer->Bind();

			Renderer::GetRenderer2D()->ResetRenderStats();

			Render::SetClearColor({ 0.3f, 0.3f, 0.3f, 0.3f });
			Render::Clear();

			m_ActiveScene->OnSceneUpdate(dt);

			m_Framebuffer->Unbind();
		}

		virtual void OnEvent(Event& event) override
		{
			//COMRADE_LOG_INFO("RECV EVENT:({}, {})", (int)event.GetEventType(), event.IsHandled());
		}

		virtual void OnImGuiRender(DeltaTime dt) override
		{
			static bool dockspace_open = true;
			static bool opt_fullscreen = true;
			static bool opt_padding = false;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->WorkPos);
				ImGui::SetNextWindowSize(viewport->WorkSize);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}
			else
			{
				dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
			}

			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			if (!opt_padding)
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

			ImGui::Begin("DockSpace", &dockspace_open, window_flags);

			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Exit"))
						Close();

					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			ImGui::Begin("Viewport");
			m_ViewPortFocused = ImGui::IsWindowFocused();
			ImVec2 viewport = ImGui::GetContentRegionAvail();
			m_ViewPort = { viewport.x, viewport.y };
			ImGui::Image((void*)m_Framebuffer->GetColorTextureID(), ImVec2(m_ViewPort.x, m_ViewPort.y), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::End();
			ImGui::PopStyleVar();

			ImGui::End();

			auto& stats = Renderer::GetRenderer2D()->GetRenderStats();
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
		MemoryRef<Scene> m_ActiveScene;
		Entity m_CameraEntity, m_SquareEntity;
		MemoryRef<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewPort;
		bool m_ViewPortFocused = false;
	};
}

int main(int argc, char** argv)
{
	Comrade::ComradeEditor* editor = new Comrade::ComradeEditor({ "Editor", 1024, 768, true });
	editor->Run();
	delete editor;
	return 0;
}
