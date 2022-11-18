#pragma once

#include "Comrade/Scene/Scene.h"

#include <entt/entt.hpp>

namespace Comrade
{
	class Entity
	{
	public:
		Entity();
		Entity(entt::entity entity, Scene* scene);

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			m_Scene->m_Registry.remove<T>(m_EntityID);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registry.get<T>(m_EntityID);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_EntityID);
		}

		bool operator==(const Entity& rhs) const { return m_EntityID == rhs.m_EntityID && m_Scene == rhs.m_Scene; }
		bool operator!=(const Entity& rhs) const { return !(*this == rhs); }
		operator bool() const { return m_EntityID != entt::null; }

		inline uint32_t GetID() const { return (uint32_t)m_EntityID; }

	private:
		entt::entity m_EntityID;
		Scene* m_Scene;
	};
}
