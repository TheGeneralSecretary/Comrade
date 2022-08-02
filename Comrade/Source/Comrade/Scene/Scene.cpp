#include "comradepch.h"
#include "Comrade/Scene/Scene.h"
#include "Comrade/Entity/Entity.h"
#include "Comrade/Entity/Components.h"
#include "Comrade/Renderer/Renderer.h"
#include "Comrade/Core/Logger.h"

namespace Comrade
{
	Scene::Scene(const std::string& name)
		: m_Name(name), m_ViewPortFocused(false)
	{
	}

	void Scene::OnSceneUpdate(DeltaTime dt)
	{
		//m_TagSystem.OnUpdate(dt, m_Registry);
		if(m_ViewPortFocused)
			m_CameraControlSystem.OnUpdate(dt, m_Registry);
		m_RenderSystem.OnUpdate(dt, m_Registry);
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

	void Scene::DestroyEntity(Entity& entity)
	{
		m_Registry.destroy((entt::entity)entity.GetID());
	}
}
