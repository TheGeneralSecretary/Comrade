#pragma once

#include "Comrade/Events/Event.h"

namespace Comrade
{
	class WindowCloseEvent : public Event
	{
	public:
		EVENT_TYPE(WindowClose)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		EVENT_TYPE(WindowResize)
	private:
		int m_Width, m_Height;
	};
}
