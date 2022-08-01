#include "comradepch.h"
#include "Comrade/Core/Window.h"
#include "Comrade/Core/Logger.h"
#include "Comrade/Events/AppEvent.h"
#include "Comrade/Input/Input.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Comrade
{
	static void APIENTRY DebugMessageCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
	{
		COMRADE_LOG_ERROR("[OpenGL Error]({}) {}", type, message);
	}

	bool Window::Init(const WindowProps& props)
	{
		m_WinData.Name = props.Name;
		m_WinData.Width = props.Width;
		m_WinData.Height = props.Height;
		m_WinData.VSync = props.VSync;

		if (!InitContext()) return false;
		if (!InitInputHandler()) return false;
		if (!InitEventSystem()) return false;
		return m_Initialized = true;
	}

	void Window::Destroy()
	{
		if (m_Initialized)
		{
			glfwSetErrorCallback(nullptr);
			glfwDestroyWindow(m_NativeWindow);
			glfwTerminate();

			Input::Destroy();

			m_Initialized = false;
		}
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_NativeWindow);
	}

	void Window::SetVSync(bool vsync)
	{
		m_WinData.VSync = vsync;
		glfwSwapInterval(m_WinData.VSync ? 1 : 0);
	}

	bool Window::InitContext()
	{
		if (!glfwInit())
		{
			COMRADE_LOG_ERROR("FAILED glfwInit");
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef COMRADE_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		m_NativeWindow = glfwCreateWindow(m_WinData.Width, m_WinData.Height, m_WinData.Name.c_str(), nullptr, nullptr);
		if (!m_NativeWindow)
		{
			COMRADE_LOG_ERROR("FAILED glfwCreateWindow for {}", m_WinData.Name);
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_NativeWindow);
		glfwSwapInterval(m_WinData.VSync ? 1 : 0);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			COMRADE_LOG_ERROR("FAILED gladLoadGLLoader");
			glfwTerminate();
			return false;
		}

		glDebugMessageCallback(DebugMessageCallback, nullptr);

		COMRADE_LOG_INFO("OpenGL: Version({}), Renderer({}), Vendor({}) ", glGetString(GL_VERSION), glGetString(GL_RENDERER), glGetString(GL_VENDOR));

		glfwShowWindow(m_NativeWindow);

		COMRADE_LOG_DEBUG("Initialized Context");
		return true;
	}

	bool Window::InitInputHandler()
	{
		if (!Input::Init())
		{
			COMRADE_LOG_ERROR("FAILED Input::Init");
			return false;
		}

		glfwSetKeyCallback(m_NativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
					Input::OnKeyEvent(KeyEventType::Press, static_cast<KeyCode>(key));
					break;
				case GLFW_RELEASE:
					Input::OnKeyEvent(KeyEventType::Release, static_cast<KeyCode>(key));
					break;
				case GLFW_REPEAT:
					Input::OnKeyEvent(KeyEventType::Repeat, static_cast<KeyCode>(key));
					break;
				default:
					break;
				}
			});

		glfwSetCharCallback(m_NativeWindow, [](GLFWwindow* window, unsigned int codepoint)
			{
				Input::OnCharEvent(KeyEventType::Press, codepoint);
			});

		glfwSetCursorPosCallback(m_NativeWindow, [](GLFWwindow* window, double xpos, double ypos)
			{
				Input::OnMouseMoveEvent({ xpos, ypos });
			});

		glfwSetScrollCallback(m_NativeWindow, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				MouseEventType evtype = yoffset > 0 ? MouseEventType::ScrollUp : MouseEventType::ScrollDown;
				Input::OnMouseScrollEvent(evtype, { xpos, ypos });
			});

		glfwSetMouseButtonCallback(m_NativeWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);

				switch (action)
				{
				case GLFW_PRESS:
					Input::OnMouseButtonEvent(MouseEventType::Press, static_cast<MouseCode>(button), { xpos, ypos });
					break;
				case GLFW_RELEASE:
					Input::OnMouseButtonEvent(MouseEventType::Release, static_cast<MouseCode>(button), { xpos, ypos });
					break;
				default:
					break;
				}
			});

		return true;
	}

	bool Window::InitEventSystem()
	{
		glfwSetWindowUserPointer(m_NativeWindow, &m_WinData);

		glfwSetWindowCloseCallback(m_NativeWindow, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.EventCallback(WindowCloseEvent{});
			});

		glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				data.EventCallback(WindowResizeEvent({ width, height }));
			});

		return true;
	}
}
