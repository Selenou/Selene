#include "slnpch.h"
#include "Selene/Core/Time.h"
#include <GLFW/glfw3.h>

namespace Selene
{
	float Time::GetTime()
	{
		return (float)glfwGetTime();
	}
}