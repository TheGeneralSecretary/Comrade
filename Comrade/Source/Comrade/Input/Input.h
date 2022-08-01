#pragma once

#include "Comrade/Input/Keyboard.h"
#include "Comrade/Input/Mouse.h"

namespace Comrade
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMousePressed(MouseCode button);

	private:
		static bool Init();
		static void Destroy();

		static void OnKeyEvent(KeyEventType type, KeyCode key);
		static void OnCharEvent(KeyEventType type, unsigned char key);
		static void OnMouseButtonEvent(MouseEventType type, MouseCode button, MousePoint<double> position);
		static void OnMouseMoveEvent(MousePoint<double> position);
		static void OnMouseScrollEvent(MouseEventType type, MousePoint<double> position);

		friend class Window;

	private:
		static bool m_Initialized;
		static Keyboard m_Keyboard;
		static Mouse m_Mouse;
	};
}
