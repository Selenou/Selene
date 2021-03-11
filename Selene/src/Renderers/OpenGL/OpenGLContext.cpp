#include "slnpch.h"
#include "OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Selene
{
	void OpenGLContext::Init()
	{
		// Create OpenGL Context
		glfwMakeContextCurrent(m_WindowHandle);

		// Init Glad
		SLN_INFO("Initializing Glad / OpenGL Rendering Context");
		int gladInitSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SLN_ASSERT(gladInitSuccess, "Failed to initialize Glad");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}