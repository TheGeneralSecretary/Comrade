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

		template<typename T>
		static MemoryRef<T> GetPanel(const std::string& name)
		{
			return std::dynamic_pointer_cast<T>(GetPanel(name));
		}

	private:
		static std::unordered_map<std::string, MemoryRef<Panel>> m_Panels;
	};
}
