#include "comradepch.h"
#include "Comrade/Systems/TagSystem.h"
#include "Comrade/Entity/Components.h"
#include "Comrade/Core/Logger.h"

namespace Comrade
{
	void TagSystem::OnUpdate(entt::registry& registry)
	{
		registry.view<TagComponent>().each([=](auto entityID, TagComponent& component)
			{
				COMRADE_LOG_INFO("Registered Entity: {}", component.Tag);
			});
	}
}
