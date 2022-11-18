#include "PanelManager.h"
#include <Comrade/Core/Logger.h>

namespace Comrade
{
	std::unordered_map<std::string, MemoryRef<Panel>> PanelManager::m_Panels;

	void PanelManager::AddPanel(const std::string& name, const MemoryRef<Panel>& panel)
	{
		if (m_Panels.find(name) == m_Panels.end())
			m_Panels[name] = panel;
	}

	MemoryRef<Panel> PanelManager::GetPanel(const std::string& name)
	{
		if (m_Panels.find(name) == m_Panels.end())
		{
			COMRADE_LOG_CRITICAL("GetPanel Not Found: {}", name);
			return nullptr;
		}

		return m_Panels[name];
	}

	void PanelManager::RenderAll()
	{
		for (auto& panel : m_Panels)
			panel.second->OnImGuiRender();
	}
}
