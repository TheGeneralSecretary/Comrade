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
			bool remove = false;
			auto& component = entity.GetComponent<T>();

			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeFlags, name.c_str());
			
			ImGui::SameLine();
			if (ImGui::Button("-"))
				remove = true;

			if (open)
			{
				func(component);
				ImGui::TreePop();
			}

			if (remove)
				entity.RemoveComponent<T>();
		}
	}

	template<typename T>
	static void AddComponentEntry(const std::string& name, Entity& entity)
	{
		if (!entity.HasComponent<T>())
		{
			if (ImGui::MenuItem(name.c_str()))
			{
				entity.AddComponent<T>();
				ImGui::CloseCurrentPopup();
			}
		}
	}

	void PropertiesPanel::OnImGuiRender()
	{
		ImGui::Begin("Properties");
		Entity& entity = SceneHierarchyPanel::GetSelectedEntity();

		if (entity)
		{
			DrawProperties(entity);

			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("AddComponent");

			if (ImGui::BeginPopup("AddComponent"))
			{
				AddComponentEntry<CameraComponent>("Camera", entity);
				AddComponentEntry<SpriteRendererComponent>("SpriteRenderer", entity);

				ImGui::EndPopup();
			}
		}

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
				glm::vec3 rotation = glm::degrees(component.Rotation);
				if(ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.1f))
					component.Rotation = glm::radians(rotation);
				ImGui::DragFloat3("Scale", glm::value_ptr(component.Scale), 0.1f);
			});

		DrawComponent<CameraComponent>("Camera", entity, [](CameraComponent& component)
			{
				ImGui::Checkbox("Primary", &component.Primary);

				auto& camera = component.Camera;

				const char* projections[] = { "Orthographic", "Perspective" };
				int projectionType = (int)camera.GetProjectionType();

				if (ImGui::BeginCombo("Projection", projections[projectionType]))
				{
					for (int i = 0; i < 2; i++)
					{
						bool selected = projectionType == i;
						if (ImGui::Selectable(projections[i], selected))
						{
							projectionType = i;
							camera.SetProjectionType((CameraProjectionType)i);
						}

						if (selected) ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == CameraProjectionType::Orthographic)
				{
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

				if (camera.GetProjectionType() == CameraProjectionType::Perspective)
				{
					float perspectiveFOV = camera.GetPerspectiveFOV();
					if (ImGui::DragFloat("FOVy", &perspectiveFOV))
						camera.SetPerspectiveFOV(perspectiveFOV);

					float perspectiveNear = camera.GetPerspectiveNear();
					if (ImGui::DragFloat("Near", &perspectiveNear))
						camera.SetPerspectiveNear(perspectiveNear);

					float perspectiveFar = camera.GetPerspectiveFar();
					if (ImGui::DragFloat("Far", &perspectiveFar))
						camera.SetPerspectiveFar(perspectiveFar);
				}
			});

		DrawComponent<SpriteRendererComponent>("SpriteRenderer", entity, [](SpriteRendererComponent& component)
			{
				ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
			});
	}
}
