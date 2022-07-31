#pragma once

#include "Comrade/Core/DeltaTime.h"
#include "Comrade/Renderer/Renderer.h"
#include "Comrade/Systems/TagSystem.h"

#include <entt/entt.hpp>

namespace Comrade
{
	class Entity;

	class Scene
	{
	public:
		void OnSceneUpdate(DeltaTime dt);
		void OnSceneRender(const MemoryRef<Renderer>& renderer);
		void OnSceneViewPortResize(int width, int height);

		Entity CreateEntity(const std::string& name = "");

	private:
		friend class Entity;
		
	private:
		entt::registry m_Registry;
		TagSystem m_TagSystem;
	};
}
