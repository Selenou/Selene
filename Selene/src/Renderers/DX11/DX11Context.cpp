#include "slnpch.h"
#include "DX11Context.h"
#include "Selene/Core/Game.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Selene
{
	void DX11Context::Init()
	{
		SLN_INFO("Initializing DX11 Rendering Context");
		m_Device->Init(glfwGetWin32Window(m_WindowHandle));
	}

	void DX11Context::SwapBuffers()
	{
		UINT isVsync = Game::GetInstance().GetWindow().IsVSync();
		m_Device->GetSwapChain()->Present(isVsync, 0);
	}
}