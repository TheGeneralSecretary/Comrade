#pragma once

#include "Comrade/Systems/System.h"

namespace Comrade
{
	class RenderSystem : public System
	{
	public:
		virtual void OnUpdate(DeltaTime dt, entt::registry& registry) override;
	};
}
