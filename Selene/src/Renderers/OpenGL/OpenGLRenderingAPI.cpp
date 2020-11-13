#include "slnpch.h"
#include "OpenGLRenderingAPI.h"
#include <glad/glad.h>

namespace Selene 
{
	void OpenGLRenderingAPI::Init()
	{

	}

	void OpenGLRenderingAPI::Clear()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}