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

	private:
		bool InitContext();

	private:
		WindowProps m_WinProps;
		GLFWwindow* m_NativeWindow;
	};
}
