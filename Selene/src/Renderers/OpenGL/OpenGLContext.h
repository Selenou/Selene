#pragma once

#include "Selene/Rendering/RenderingContext.h"

struct GLFWwindow;

namespace Selene
{
	class OpenGLContext : public RenderingContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle)
			: m_WindowHandle(windowHandle) {}
	public:
		virtual void Init() override;
		virtual void Destroy() override {};
	private:
		GLFWwindow* m_WindowHandle;
	};
} 