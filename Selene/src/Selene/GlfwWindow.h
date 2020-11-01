#pragma once

#include "Window.h"
#include <GLFW/glfw3.h>

namespace Selene {

	class GlfwWindow : public Window
	{
	public:
		GlfwWindow(const WindowData& data);
		virtual ~GlfwWindow();
	public:
		void Init(const WindowData& data) override;
		void Update() override;
		void Destroy() override;
		void SetVSync(bool enabled) override;
	private:
		GLFWwindow* m_Window;
	};

}