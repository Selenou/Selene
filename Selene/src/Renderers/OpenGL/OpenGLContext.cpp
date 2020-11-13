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
		SLN_ENGINE_INFO("Initializing Glad");
		int gladInitSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (!gladInitSuccess)
		{
			SLN_ENGINE_CRITICAL("Failed to initialize Glad");
		}

		SLN_ENGINE_INFO("OpenGL Vendor : {0}", glGetString(GL_VENDOR));
		SLN_ENGINE_INFO("OpenGL Renderer : {0}", glGetString(GL_RENDERER));
		SLN_ENGINE_INFO("OpenGL Version : {0}", glGetString(GL_VERSION));
		SLN_ENGINE_INFO("OpenGL Shading Language Version : {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));
	}
}