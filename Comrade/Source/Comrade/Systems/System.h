#pragma once

#include "Comrade/Core/DeltaTime.h"

#include <entt/entt.hpp>

namespace Comrade
{
	class System
	{
	public:
		virtual ~System() = default;
		virtual void OnUpdate(DeltaTime dt, entt::registry& registry) = 0;
	};
}
