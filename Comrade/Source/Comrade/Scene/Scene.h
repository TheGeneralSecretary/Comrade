#pragma once

#include "Comrade/Core/DeltaTime.h"
#include "Comrade/Systems/TagSystem.h"

#include <entt/entt.hpp>

namespace Comrade
{
	class Entity;

	class Scene
	{
	public:
		void OnSceneUpdate(DeltaTime dt);
		Entity CreateEntity(const std::string& name = "");

	private:
		friend class Entity;
		
	private:
		entt::registry m_Registry;
		TagSystem m_TagSystem;
	};
}
