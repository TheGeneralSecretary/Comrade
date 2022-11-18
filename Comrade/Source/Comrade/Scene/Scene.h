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
		Scene(const std::string& name = "Untitled");
		void OnSceneUpdate(DeltaTime dt);
		void OnSceneViewPortResize(int width, int height);

		Entity CreateEntity(const std::string& name = "");
		void DestroyEntity(Entity& entity);

		inline void SetName(const std::string& name) { m_Name = name; }
		inline const std::string& GetName() const { return m_Name; }

		inline void SetViewPortFocus(bool focus) { m_ViewPortFocused = focus; }
		
		inline entt::registry& GetRegistry() { return m_Registry; }

	private:
		friend class Entity;
		
	private:
		bool m_ViewPortFocused;
		std::string m_Name;
		entt::registry m_Registry;
		TagSystem m_TagSystem;
		CameraControlSystem m_CameraControlSystem;
		RenderSystem m_RenderSystem;
	};
}
