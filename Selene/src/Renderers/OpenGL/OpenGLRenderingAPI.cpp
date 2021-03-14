#include "slnpch.h"
#include "OpenGLRenderingAPI.h"
#include "Selene/Config.h"
#include <glad/glad.h>

namespace Selene 
{
	void OpenGLRenderingAPI::Init()
	{
		if (Config::DEPTH_BUFER_ENABLED)
		{
			glEnable(GL_DEPTH_TEST);
		}
		
		if (Config::FACE_CULLING_ENABLED)
		{
			glEnable(GL_CULL_FACE);
		}
	}

	void OpenGLRenderingAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderingAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
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