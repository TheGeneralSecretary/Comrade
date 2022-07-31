#pragma once

#include <functional>

namespace Comrade
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize,
	};

#define EVENT_TYPE(type) \
	static EventType GetType() { return EventType::type; }\
	virtual EventType GetEventType() const override { return GetType(); }\

	class Event
	{
	public:
		virtual ~Event() = default;
		virtual EventType GetEventType() const = 0;

		inline bool IsHandled() const { return m_Handled; }

		template<typename T>
		void Dispatch(Event& event, std::function<bool(T&)> cb)
		{
			if (event.GetEventType() == T::GetType())
				event.m_Handled = cb((T&)event);
		}

	protected:
		bool m_Handled = false;
	};

	using EventCallbackFn = std::function<void(Event&)>;
}
