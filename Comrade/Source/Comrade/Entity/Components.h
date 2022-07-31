#pragma once

#include "Comrade/Scene/SceneCamera.h"

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Comrade
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 Translation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale{ 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 transform(1.0f);
			transform = glm::translate(transform, Translation);
			transform = glm::rotate(transform, glm::radians(Rotation.x), { 1, 0, 0 });
			transform = glm::rotate(transform, glm::radians(Rotation.y), { 0, 1, 0 });
			transform = glm::translate(transform, { Scale * 0.5f });
			transform = glm::rotate(transform, glm::radians(Rotation.z), { 0, 0, 1 });
			transform = glm::translate(transform, { Scale * -0.5f });
			transform = glm::scale(transform, Scale);
			return transform;
		}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = false;
		bool Fixed = false;

		CameraComponent() = default;
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};
}
