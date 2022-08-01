#include "SceneHierarchyPanel.h"
#include <Comrade/Entity/Components.h>
#include <Comrade/Input/Input.h>

#include <imgui.h>
#include <string>

namespace Comrade
{
	Entity SceneHierarchyPanel::m_SelectedEntity;

	SceneHierarchyPanel::SceneHierarchyPanel(const MemoryRef<Scene>& scene)
		: m_Scene(scene)
	{
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Scene->GetRegistry().each([&](auto entityID)
			{
				Entity entity{ entityID, m_Scene.get() };
				DrawEntity(entity);
			});

		if (Input::IsMousePressed(MouseCode::Button1) && ImGui::IsWindowHovered())
			m_SelectedEntity = {};

		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Entity"))
				m_Scene->CreateEntity("Entity");

			ImGui::EndPopup();
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntity(Entity& entity)
	{
		bool removed = false;
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool open = ImGui::TreeNodeEx((void*)entity.GetID(), flags, tag.c_str());

		if (ImGui::IsItemClicked())
			m_SelectedEntity = entity;

		if (ImGui::BeginPopupContextItem(0, 1))
		{
			if (ImGui::MenuItem("Delete Entity"))
				removed = true;

			ImGui::EndPopup();
		}

		if (open)
			ImGui::TreePop();

		if(removed)
		{
			m_Scene->DestroyEntity(entity);
			if (m_SelectedEntity == entity) m_SelectedEntity = {};
		}
	}
}
