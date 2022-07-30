#include "comradepch.h"
#include "Comrade/Utils/DateTime.h"

#include <GLFW/glfw3.h>

namespace Comrade
{
	double DateTime::GetTimeSeconds()
	{
		return glfwGetTime();
	}
}
