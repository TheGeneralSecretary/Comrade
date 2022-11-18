#include "comradepch.h"
#include "Comrade/Scene/Scene.h"
#include "Comrade/Scene/Entity.h"
#include "Comrade/Scene/Components.h"
#include "Comrade/Core/Logger.h"

namespace Comrade
{
	void Scene::OnSceneUpdate(DeltaTime dt)
	{
		m_TagSystem.OnUpdate(m_Registry);
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity{ m_Registry.create(), this };
		auto& tag = entity.AddComponent<TagComponent>(name);
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}
}
