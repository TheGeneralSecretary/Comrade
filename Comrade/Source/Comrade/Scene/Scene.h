#pragma once

#include "Comrade/Core/DeltaTime.h"
#include "Comrade/Systems/TagSystem.h"
#include "Comrade/Systems/CameraControlSystem.h"
#include "Comrade/Systems/RenderSystem.h"

#include <entt/entt.hpp>

namespace Comrade
{
	class Entity;

	class Scene
	{
	public:
		void OnSceneUpdate(DeltaTime dt);
		void OnSceneViewPortResize(int width, int height);

		Entity CreateEntity(const std::string& name = "");
		void DestroyEntity(Entity& entity);

		inline entt::registry& GetRegistry() { return m_Registry; }

	private:
		friend class Entity;
		
	private:
		entt::registry m_Registry;
		TagSystem m_TagSystem;
		CameraControlSystem m_CameraControlSystem;
		RenderSystem m_RenderSystem;
	};
}
