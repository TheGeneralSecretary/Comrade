#include "PropertiesPanel.h"
#include "SceneHierarchyPanel.h"
#include <Comrade/Entity/Components.h>

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <string>

namespace Comrade
{
	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity& entity, UIFunction func)
	{
		const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap;

		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();

			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeFlags, name.c_str());
			if (open)
			{
				func(component);
				ImGui::TreePop();
			}
		}
	}

	void PropertiesPanel::OnImGuiRender()
	{
		ImGui::Begin("Properties");
		Entity& entity = SceneHierarchyPanel::GetSelectedEntity();

		if (entity)
			DrawProperties(entity);

		ImGui::End();
	}

	void PropertiesPanel::DrawProperties(Entity& entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			char buff[1024] = {};
			strcpy_s(buff, sizeof(buff), tag.c_str());

			if (ImGui::InputText("Tag", buff, sizeof(buff)))
				tag = std::string(buff);
		}

		DrawComponent<TransformComponent>("Transform", entity, [](TransformComponent& component)
			{
				ImGui::DragFloat3("Translation", glm::value_ptr(component.Translation), 0.1f);
				ImGui::DragFloat3("Rotation", glm::value_ptr(component.Rotation), 0.1f);
				ImGui::DragFloat3("Scale", glm::value_ptr(component.Scale), 0.1f);
			});

		DrawComponent<CameraComponent>("Camera", entity, [](CameraComponent& component)
			{
				ImGui::Checkbox("Primary", &component.Primary);

				auto& camera = component.Camera;
				if (camera.GetProjectionType() == CameraProjectionType::Orthographic)
				{
					if (ImGui::BeginCombo("Projection", "Orthographic"))
						ImGui::EndCombo();

					ImGui::Checkbox("Fixed", &component.Fixed);

					float orthoSize = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
						camera.SetOrthographicSize(orthoSize);

					float orthoNear = camera.GetOrthographicNear();
					if (ImGui::DragFloat("Near", &orthoNear))
						camera.SetOrthographicNear(orthoNear);

					float orthoFar = camera.GetOrthographicFar();
					if (ImGui::DragFloat("Far", &orthoFar))
						camera.SetOrthographicFar(orthoFar);
				}
			});

		DrawComponent<SpriteRendererComponent>("SpriteRenderer", entity, [](SpriteRendererComponent& component)
			{
				ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
			});
	}
}
