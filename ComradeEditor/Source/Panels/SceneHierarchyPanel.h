#pragma once

#include "Panel.h"
#include <Comrade/Utils/Memory.h>
#include <Comrade/Scene/Scene.h>
#include <Comrade/Entity/Entity.h>

namespace Comrade
{
	class SceneHierarchyPanel : public Panel
	{
	public:
		SceneHierarchyPanel(const MemoryRef<Scene>& scene);

		virtual void OnImGuiRender() override;

		static inline Entity& GetSelectedEntity() { return m_SelectedEntity; }

	private:
		void DrawEntity(Entity& entity);

	private:
		MemoryRef<Scene> m_Scene;
		static Entity m_SelectedEntity;
	};
}
