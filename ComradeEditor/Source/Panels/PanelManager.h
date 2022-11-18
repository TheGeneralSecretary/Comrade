#pragma once

#include "Panel.h"
#include <Comrade/Utils/Memory.h>

#include <unordered_map>
#include <string>

namespace Comrade
{
	class PanelManager
	{
	public:
		static void AddPanel(const std::string& name, const MemoryRef<Panel>& panel);
		static MemoryRef<Panel> GetPanel(const std::string& name);
		static void RenderAll();

	private:
		static std::unordered_map<std::string, MemoryRef<Panel>> m_Panels;
	};
}
