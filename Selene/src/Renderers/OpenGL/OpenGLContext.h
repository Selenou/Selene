#pragma once

#include "Selene/Rendering/Context.h"

struct GLFWwindow;

namespace Selene
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {}
	public:
		virtual void Init() override;
		virtual void Destroy() override {};
	private:
		GLFWwindow* m_WindowHandle;
	};
}