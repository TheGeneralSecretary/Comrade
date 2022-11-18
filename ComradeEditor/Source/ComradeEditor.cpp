#include "comradepch.h"

#include "Panels/PanelManager.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/PropertiesPanel.h"

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
#include <Comrade/Scene/SceneSerializer.h>
#include <Comrade/Scene/EditorCamera.h>

#include <Comrade/Platform/FileDialog.h>

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
			m_ActiveScene = CreateRef<Scene>("Untitled");
			m_Framebuffer = CreateRef<Framebuffer>(props.Width, props.Height);

			PanelManager::AddPanel("SceneHierarchyPanel", CreateRef<SceneHierarchyPanel>(m_ActiveScene));
			PanelManager::AddPanel("PropertiesyPanel", CreateRef<PropertiesPanel>());

			m_EditorCamera = CreateRef<EditorCamera>(45.0f, ((float)props.Width / (float)props.Height), 0.1f, 100.0f);
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
				m_EditorCamera->SetViewPort(m_ViewPort.x, m_ViewPort.y);
			}

			if (m_ViewPortFocused)
			{
				m_EditorCamera->OnUpdate(dt);
			}

			m_FPS = (1.0f / dt);

			m_Framebuffer->Bind();

			Renderer::GetRenderer2D()->ResetRenderStats();

			Render::SetClearColor({ 0.3f, 0.3f, 0.3f, 0.3f });
			Render::Clear();

			//m_ActiveScene->OnSceneRuntime(dt);
			m_ActiveScene->OnSceneEditor(dt, *m_EditorCamera);

			m_Framebuffer->Unbind();
		}

		virtual void OnEvent(Event& event) override
		{
			//COMRADE_LOG_INFO("RECV EVENT:({}, {})", (int)event.GetEventType(), event.IsHandled());
			m_EditorCamera->OnEvent(event);
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
					if (ImGui::MenuItem("New"))
						NewScene();

					if (ImGui::MenuItem("Open"))
						OpenScene();

					if (ImGui::MenuItem("Save"))
						SaveScene();

					if (ImGui::MenuItem("Save As"))
						SaveSceneAs();

					if (ImGui::MenuItem("Exit"))
						Close();

					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			PanelManager::RenderAll();

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			ImGui::Begin("Viewport");
			m_ViewPortFocused = ImGui::IsWindowFocused();
			m_ActiveScene->SetViewPortFocus(m_ViewPortFocused);
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
			ImGui::NewLine();
			ImGui::Text("Scene Stats:");
			ImGui::Text("FPS: %.2f", m_FPS);
			ImGui::Text("Active Scene: %s", m_ActiveScene->GetName().c_str());
			ImGui::End();
		}

	private:
		void NewScene()
		{
			m_ActiveScene = CreateRef<Scene>();
			PanelManager::GetPanel<SceneHierarchyPanel>("SceneHierarchyPanel")->SetScene(m_ActiveScene);
			m_ActiveScene->OnSceneViewPortResize(m_ViewPort.x, m_ViewPort.y);
		}

		void OpenScene()
		{
			std::string filepath = FileDialog::OpenFile("Comrade Scene (*.comrade)\0*.comrade\0");
			if (!filepath.empty())
			{
				m_ActiveScene = CreateRef<Scene>();
				PanelManager::GetPanel<SceneHierarchyPanel>("SceneHierarchyPanel")->SetScene(m_ActiveScene);
				SceneSerializer::Deserialize(m_ActiveScene, filepath);
				m_ActiveScene->OnSceneViewPortResize(m_ViewPort.x, m_ViewPort.y);
				m_ScenePath = filepath;
			}
		}

		void SaveScene()
		{
			if (!m_ScenePath.empty())
			{
				SceneSerializer::Serialize(m_ActiveScene, m_ScenePath);
				return;
			}

			SaveSceneAs();
		}

		void SaveSceneAs()
		{
			std::string filepath = FileDialog::SaveFile("Comrade Scene (*.comrade)\0*.comrade\0");
			if (!filepath.empty())
			{
				SceneSerializer::Serialize(m_ActiveScene, filepath);
				m_ScenePath = filepath;
			}
		}

	private:
		double m_FPS = 0.0f;
		MemoryRef<Scene> m_ActiveScene;
		MemoryRef<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewPort;
		bool m_ViewPortFocused = false;
		std::string m_ScenePath;
		MemoryRef<EditorCamera> m_EditorCamera;
	};
}

int main(int argc, char** argv)
{
	Comrade::ComradeEditor* editor = new Comrade::ComradeEditor({ "Editor", 1024, 768, true });
	editor->Run();
	delete editor;
	return 0;
}
