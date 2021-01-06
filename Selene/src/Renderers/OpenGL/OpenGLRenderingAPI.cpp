#include "slnpch.h"
#include "OpenGLRenderingAPI.h"
#include <glad/glad.h>

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
				SLN_ENGINE_CRITICAL(message); 
				return;
			case GL_DEBUG_SEVERITY_MEDIUM:  
				SLN_ENGINE_ERROR(message); 
				return;
			case GL_DEBUG_SEVERITY_LOW:   
				SLN_ENGINE_WARN(message); 
				return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: 
				SLN_ENGINE_TRACE(message); 
				return;
		}
	}

	void OpenGLRenderingAPI::Init()
	{
		// Debug Output
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

		// Fill Rendering Info
		auto& info = RenderingAPI::GetInfo();
		info.API = "OpenGL";
		info.Vendor = (const char*)glGetString(GL_VENDOR);
		info.Renderer = (const char*)glGetString(GL_RENDERER);
		info.Version = (const char*)glGetString(GL_VERSION);
		info.ShadingLanguageVersion = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	}

	void OpenGLRenderingAPI::Clear()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderingAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderingAPI::DrawIndexed(uint32_t count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}