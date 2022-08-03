#include "comradepch.h"
#include "Comrade/ImGui/CImGui.h"
#include "Comrade/Core/Application.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <ImGuizmo.h>

namespace Comrade
{
	bool CImGui::Init()
	{
		ImGui::CreateContext();
		ImGui::GetIO().DisplaySize = { (float)Application::Get()->GetWindow().GetWidth(), (float)Application::Get()->GetWindow().GetHeight() };
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//ImGui::GetIO().Fonts->AddFontFromFileTTF("../Assets/Fonts/arial.ttf", 16);

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(Application::Get()->GetWindow().GetNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 460 core");
		return m_Initialized = true;
	}

	void CImGui::Destroy()
	{
		if (m_Initialized)
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}
	}

	void CImGui::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
	}

	void CImGui::EngFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			auto* bakcc = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(bakcc);
		}
	}
}
