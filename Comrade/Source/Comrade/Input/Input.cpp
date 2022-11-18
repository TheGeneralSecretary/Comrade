#include "comradepch.h"
#include "Comrade/Input/Input.h"

namespace Comrade
{
	bool Input::m_Initialized = false;
	Keyboard Input::m_Keyboard;
	Mouse Input::m_Mouse;

	bool Input::Init()
	{
		if (!m_Keyboard.Init()) return false;
		if (!m_Mouse.Init()) return false;
		return m_Initialized = true;
	}

	void Input::Destroy()
	{
		if (m_Initialized)
		{
			m_Keyboard.Destroy();
			m_Mouse.Destroy();
			m_Initialized = false;
		}
	}

	bool Input::IsKeyPressed(KeyCode key)
	{
		return m_Keyboard.IsKeyPressed(key);
	}

	bool Input::IsMousePressed(MouseCode button)
	{
		return m_Mouse.IsButtonDown(button);
	}

	void Input::OnKeyEvent(KeyEventType type, KeyCode key)
	{
		switch (type)
		{
		case KeyEventType::Press:
			m_Keyboard.OnKeyPressedEvent(key);
			break;
		case KeyEventType::Release:
			m_Keyboard.OnKeyReleasedEvent(key);
			break;
		case KeyEventType::Repeat:
			if (m_Keyboard.IsKeyAutoRepeat())
				m_Keyboard.OnKeyPressedEvent(key);
			break;
		default:
			break;
		}
	}

	void Input::OnCharEvent(KeyEventType type, unsigned char key)
	{
		switch (type)
		{
		case KeyEventType::Press:
			m_Keyboard.OnCharEvent(key);
			break;
		case KeyEventType::Repeat:
			if (m_Keyboard.IsCharAutoRepeat())
				m_Keyboard.OnCharEvent(key);
			break;
		default:
			break;
		}
	}

	void Input::OnMouseButtonEvent(MouseEventType type, MouseCode button, MousePoint<double> position)
	{
		switch (type)
		{
		case MouseEventType::Press:
			m_Mouse.OnMousePressedEvent(button, position);
			break;
		case MouseEventType::Release:
			m_Mouse.OnMouseReleasedEvent(button, position);
			break;
		default:
			break;
		}
	}

	void Input::OnMouseMoveEvent(MousePoint<double> position)
	{
		m_Mouse.OnMouseMoveEvent(position);
	}

	void Input::OnMouseScrollEvent(MouseEventType type, MousePoint<double> position)
	{
		switch (type)
		{
		case MouseEventType::ScrollUp:
			m_Mouse.OnMouseScrollUpEvent(position);
			break;
		case MouseEventType::ScrollDown:
			m_Mouse.OnMouseScrollDownEvent(position);
			break;
		default:
			break;
		}
	}
}
