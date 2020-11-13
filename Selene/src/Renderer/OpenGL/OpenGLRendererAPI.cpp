#include "slnpch.h"
#include "OpenGLRendererAPI.h"
#include <glad/glad.h>

namespace Selene 
{
	void OpenGLRendererAPI::Init()
	{
		SLN_ENGINE_INFO("OpenGL Vendor : {0}", glGetString(GL_VENDOR));
		SLN_ENGINE_INFO("OpenGL Renderer : {0}", glGetString(GL_RENDERER));
		SLN_ENGINE_INFO("OpenGL Version : {0}", glGetString(GL_VERSION));
		SLN_ENGINE_INFO("OpenGL Shading Language Version : {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	void OpenGLRendererAPI::Clear()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}