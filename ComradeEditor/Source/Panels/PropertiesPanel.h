#pragma once

#include "Panel.h"
#include <Comrade/Entity/Entity.h>

namespace Comrade
{
	class PropertiesPanel : public Panel
	{
	public:
		virtual void OnImGuiRender() override;

	private:
		void DrawProperties(Entity& entity);
	};
}
