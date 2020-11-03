#pragma once

#include "Window.h"
#include <GLFW/glfw3.h>

namespace Selene {

	struct GlfwWindowData
	{
		std::string Title;
		uint32_t Width, Height;
		bool VSync;

		Window::EventCallback EventCallback;
	};

	class GlfwWindow : public Window
	{
	public:
		GlfwWindow(const WindowSettings& settings);
		virtual ~GlfwWindow();
	public:
		void Update() override;
		inline void SetEventCallback(const EventCallback& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
	protected:
		void Init() override;
		void Destroy() override;
	private:
		GLFWwindow* m_Window;
		GlfwWindowData m_Data;
	};

}