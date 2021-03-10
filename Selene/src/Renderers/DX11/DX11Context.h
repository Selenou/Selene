#pragma once
#include "Selene/Rendering/Context.h"

struct GLFWwindow;

namespace Selene
{
	class DX11Context : public Context
	{
	public:
		DX11Context(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {}
	public:
		virtual void Init() override;
		virtual void Destroy() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}