#include "slnpch.h"
#include "OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Selene/Rendering/RenderingAPI.h"

namespace Selene
{
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			SLN_CRITICAL(message);
			return;
		case GL_DEBUG_SEVERITY_MEDIUM:
			SLN_ERROR(message);
			return;
		case GL_DEBUG_SEVERITY_LOW:
			SLN_WARN(message);
			return;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			SLN_TRACE(message);
			return;
		}
	}

	void OpenGLContext::Init()
	{
		// Create OpenGL Context
		glfwMakeContextCurrent(m_WindowHandle);

		// Init Glad
		SLN_INFO("Initializing Glad / OpenGL Rendering Context");
		int gladInitSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SLN_ASSERT(gladInitSuccess, "Failed to initialize Glad");

		// Fill Rendering Info
		auto& info = RenderingAPI::GetInfo();
		info.API = "OpenGL";
		info.Version = (const char*)glGetString(GL_VERSION);
		info.Vendor = (const char*)glGetString(GL_VENDOR);
		info.Renderer = (const char*)glGetString(GL_RENDERER);

		// Debug Output
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}