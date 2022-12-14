#include "comradepch.h"
#include "Comrade/Input/Keyboard.h"

namespace Comrade
{
	bool Keyboard::Init()
	{
		for (int i = 0; i < MAX_KEYBOARD_KEYS; i++)
			m_KeyState[i] = false;

		m_AutoRepeatKey = true;
		m_AutoRepeatChar = true;
		return m_Initialized = true;
	}

	void Keyboard::Destroy()
	{
		if (m_Initialized)
			m_Initialized = false;
	}

	void Keyboard::OnKeyPressedEvent(KeyCode key)
	{
		m_KeyState[key] = true;
		m_KeyBuffer.push(KeyEvent(KeyEventType::Press, key));
	}

	void Keyboard::OnKeyReleasedEvent(KeyCode key)
	{
		m_KeyState[key] = false;
		m_KeyBuffer.push(KeyEvent(KeyEventType::Release, key));
	}

	void Keyboard::OnCharEvent(unsigned char key)
	{
		m_CharBuffer.push(key);
	}

	KeyEvent Keyboard::GetEvent()
	{
		if (!m_KeyBuffer.empty())
		{
			KeyEvent ev = m_KeyBuffer.front();
			m_KeyBuffer.pop();
			return ev;
		}

		return { KeyEventType::Invalid, KeyCode::Unknown };
	}

	unsigned char Keyboard::GetChar()
	{
		if (!m_CharBuffer.empty())
		{
			unsigned char c = m_CharBuffer.front();
			m_CharBuffer.pop();
			return c;
		}

		return 0;
	}

	void Keyboard::SetAutoRepeatKey(bool status)
	{
		m_AutoRepeatKey = status;
	}

	void Keyboard::SetAutoRepeatChar(bool status)
	{
		m_AutoRepeatChar = status;
	}

	bool Keyboard::IsKeyPressed(KeyCode key) const
	{
		return m_KeyState[key];
	}

	bool Keyboard::IsKeyBufferEmpty() const
	{
		return m_KeyBuffer.empty();
	}

	bool Keyboard::IsCharBufferEmpty() const
	{
		return m_CharBuffer.empty();
	}

	bool Keyboard::IsKeyAutoRepeat() const
	{
		return m_AutoRepeatKey;
	}

	bool Keyboard::IsCharAutoRepeat() const
	{
		return m_AutoRepeatChar;
	}
}
