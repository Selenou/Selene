#pragma once

#include "Selene/Rendering/RenderingContext.h"

struct GLFWwindow;

namespace Selene 
{
	class VulkanContext : public RenderingContext
	{
	public:
		VulkanContext(GLFWwindow* windowHandle)
			: m_WindowHandle(windowHandle) {}
	public:
		void Init() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}