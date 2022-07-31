#pragma once

#include "Comrade/Events/Event.h"

#include <string>

struct GLFWwindow;

namespace Comrade
{
	struct WindowProps
	{
		std::string Name;
		int Width;
		int Height;
		bool VSync;
	};

	class Window
	{
	public:
		bool Init(const WindowProps& props);
		void Update();
		void SetVSync(bool vsync);

		inline const auto& GetNativeWindow() const { return m_NativeWindow; }
		inline int GetWidth() const { return m_WinData.Width; }
		inline int GetHeight() const { return m_WinData.Height; }
		
		inline void SetEventCallback(const EventCallbackFn& cb) { m_WinData.EventCallback = cb; }

	private:
		bool InitContext();
		bool InitEventSystem();

	private:
		struct WindowData
		{
			std::string Name;
			int Width;
			int Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_WinData;
		GLFWwindow* m_NativeWindow;
	};
}
