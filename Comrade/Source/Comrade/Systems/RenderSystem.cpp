#include "comradepch.h"
#include "Comrade/Systems/RenderSystem.h"
#include "Comrade/Entity/Components.h"
#include "Comrade/Renderer/Renderer.h"

namespace Comrade
{
	void RenderSystem::OnUpdate(DeltaTime dt, entt::registry& registry)
	{
		Camera* primaryCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;

		auto cameras = registry.group<CameraComponent>(entt::get<TransformComponent>);
		for (auto entity : cameras)
		{
			auto& [camera, transform] = cameras.get<CameraComponent, TransformComponent>(entity);
			if (camera.Primary)
			{
				primaryCamera = &camera.Camera;
				cameraTransform = &transform.GetTransform();
				break;
			}
		}

		if (primaryCamera)
		{
			Renderer::GetRenderer2D()->BeginRender(*primaryCamera, *cameraTransform);

			auto sprites = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : sprites)
			{
				auto& [transform, sprite] = sprites.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer::GetRenderer2D()->RenderQuad(transform.GetTransform(), sprite.Color);
			}

			Renderer::GetRenderer2D()->EndRender();
		}
	}
}
