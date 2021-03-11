#pragma once

#include "Selene/Core/Window.h"
#include "Selene/Rendering/Context.h"
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
		virtual void SwapBuffers() override;
		virtual void PollEvents() override;
		inline virtual unsigned int GetWidth() const override { return m_Data.Width; }
		inline virtual unsigned int GetHeight() const override { return m_Data.Height; }
		inline virtual bool IsVSync() const override { return m_Data.VSync; }
	    inline virtual void SetEventCallback(const EventCallback& callback) override { m_Data.EventCallback = callback; }
		inline virtual void* GetNativeWindow() const override { return m_Window; }
		inline virtual Context* GetRenderingContext() override { return m_RenderingContext.get(); };
		virtual void SetVSync(bool enabled) override;
	protected:
		virtual void Init() override;
		virtual void Destroy() override;
	private:
		void SetWindowIcon();
	private:
		std::unique_ptr<Context> m_RenderingContext;
		GLFWwindow* m_Window;
		GlfwWindowData m_Data;
	};
}