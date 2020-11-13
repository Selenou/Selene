#pragma once

#include "Selene/Window.h"
#include "Selene/Rendering/RenderingContext.h"
#include <GLFW/glfw3.h>

namespace Selene 
{
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
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		inline void SetEventCallback(const EventCallback& callback) override { m_Data.EventCallback = callback; }
		inline virtual void* GetNativeWindow() const { return m_Window; }
		void SetVSync(bool enabled) override;
	protected:
		void Init() override;
		void Destroy() override;
	private:
		std::unique_ptr<RenderingContext> m_RenderingContext;
		GLFWwindow* m_Window;
		GlfwWindowData m_Data;
	};
}