#include "comradepch.h"
#include "Comrade/Entity/Entity.h"

namespace Comrade
{
	Entity::Entity()
		: m_EntityID(entt::null), m_Scene(nullptr)
	{}

	Entity::Entity(entt::entity entity, Scene* scene)
		: m_EntityID(entity), m_Scene(scene)
	{}
}
