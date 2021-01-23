#include "slnpch.h"
#include "Selene/Core/Input.h"
#include "Selene/Core/Game.h"
#include <GLFW/glfw3.h>

namespace Selene
{
	bool Input::IsKeyPressed(KeyCode keycode)
	{
		auto* window = static_cast<GLFWwindow*>(Game::GetInstance().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(KeyCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Game::GetInstance().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	Input::MousePosition Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Game::GetInstance().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return MousePosition({ (float)x, (float)y });
	}
}