#pragma once

#include "Selene/Rendering/Context.h"

struct GLFWwindow;

namespace Selene 
{
	class VulkanContext : public Context
	{
	public:
		VulkanContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {}
	public:
		virtual void Init() override;
		virtual void Destroy() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}