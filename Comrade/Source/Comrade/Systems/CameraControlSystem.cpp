#include "comradepch.h"
#include "Comrade/Systems/CameraControlSystem.h"
#include "Comrade/Entity/Components.h"
#include "Comrade/Input/Input.h"

namespace Comrade
{
	void CameraControlSystem::OnUpdate(DeltaTime dt, entt::registry& registry)
	{
		auto cameras = registry.group<CameraComponent>(entt::get<TransformComponent>);
		for (auto entity : cameras)
		{
			auto& [cameraComponent, transformComponent] = cameras.get<CameraComponent, TransformComponent>(entity);
			if (cameraComponent.Primary)
			{
				float speed = 1.0f;
				auto& translation = transformComponent.Translation;

				if (Input::IsKeyPressed(KeyCode::A))
					translation.x -= speed * dt;
				if (Input::IsKeyPressed(KeyCode::D))
					translation.x += speed * dt;
				if (Input::IsKeyPressed(KeyCode::W))
					translation.y += speed * dt;
				if (Input::IsKeyPressed(KeyCode::S))
					translation.y -= speed * dt;
			}
		}
	}
}
