#include "slnpch.h"
#include "Selene/Input.h"
#include "Selene/Game.h"
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
		return MousePosition();
	}
}