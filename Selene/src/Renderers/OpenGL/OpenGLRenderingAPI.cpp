#include "slnpch.h"
#include "OpenGLRenderingAPI.h"
#include "Selene/Config.h"
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

		if (Config::DEPTH_BUFER_ENABLED)
		{
			glEnable(GL_DEPTH_TEST);
		}
		
		if (Config::FACE_CULLING_ENABLED)
		{
			glEnable(GL_CULL_FACE);
		}

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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderingAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderingAPI::DrawIndexed(uint32_t count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderingAPI::DrawIndexedBaseVertex(uint32_t count, uint32_t offset)
	{
		glDrawElementsBaseVertex(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr, offset);
	}

	void OpenGLRenderingAPI::DrawInstanced(uint32_t indiceCount, uint32_t instanceCount)
	{
		glDrawArraysInstanced(GL_TRIANGLES, 0, indiceCount, instanceCount);
	}
}