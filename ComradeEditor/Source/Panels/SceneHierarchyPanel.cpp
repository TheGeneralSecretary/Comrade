#include "SceneHierarchyPanel.h"
#include <Comrade/Entity/Components.h>

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

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntity(Entity& entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool open = ImGui::TreeNodeEx((void*)entity.GetID(), flags, tag.c_str());

		if (ImGui::IsItemClicked())
			m_SelectedEntity = entity;

		if (open)
			ImGui::TreePop();
;	}
}
