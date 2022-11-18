#include "comradepch.h"
#include "Comrade/Platform/FileDialog.h"
#include "Comrade/Core/Application.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <commdlg.h>

namespace Comrade
{
	std::string FileDialog::OpenFile(const char* filter)
	{
		char szFile[256] = {};
		OPENFILENAMEA ofn = {};
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = glfwGetWin32Window(Application::Get()->GetWindow().GetNativeWindow());
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&ofn))
			return ofn.lpstrFile;

		return {};
	}
	
	std::string FileDialog::SaveFile(const char* filter)
	{
		char szFile[256] = {};
		OPENFILENAMEA ofn = {};
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = glfwGetWin32Window(Application::Get()->GetWindow().GetNativeWindow());
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileNameA(&ofn))
			return ofn.lpstrFile;

		return {};
	}
}
