#include "comradepch.h"
#include "Comrade/Scene/Scene.h"
#include "Comrade/Entity/Entity.h"
#include "Comrade/Entity/Components.h"
#include "Comrade/Core/Logger.h"

namespace Comrade
{
	Camera* primaryCamera = nullptr;
	glm::mat4* cameraTransform = nullptr;

	void Scene::OnSceneUpdate(DeltaTime dt)
	{
		m_TagSystem.OnUpdate(dt, m_Registry);
		m_CameraControlSystem.OnUpdate(dt, m_Registry);

		auto cameras = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
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
	}

	void Scene::OnSceneRender(const MemoryRef<Renderer>& renderer)
	{
		if (primaryCamera)
		{
			renderer->GetRenderer2D()->BeginRender(*primaryCamera, *cameraTransform);

			auto sprites = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : sprites)
			{
				auto& [transform, sprite] = sprites.get<TransformComponent, SpriteRendererComponent>(entity);
				renderer->GetRenderer2D()->RenderQuad(transform.GetTransform(), sprite.Color);
			}

			renderer->GetRenderer2D()->EndRender();
		}
	}

	void Scene::OnSceneViewPortResize(int width, int height)
	{
		auto cameras = m_Registry.view<CameraComponent>();
		for (auto entity : cameras)
		{
			auto& camera = cameras.get<CameraComponent>(entity);
			if (!camera.Fixed)
			{
				camera.Camera.SetViewPort(width, height);
			}
		}
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity{ m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>(name);
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}
}
