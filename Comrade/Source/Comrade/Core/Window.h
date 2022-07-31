#pragma once

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
		inline int GetWidth() const { return m_WinProps.Width; }
		inline int GetHeight() const { return m_WinProps.Height; }

	private:
		bool InitContext();

	private:
		WindowProps m_WinProps;
		GLFWwindow* m_NativeWindow;
	};
}
