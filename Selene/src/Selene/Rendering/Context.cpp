#include "slnpch.h"
#include "Context.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLContext.h"

namespace Selene
{
	std::unique_ptr<Context> Context::Create(void* window)
	{
		SLN_INFO("Creating Rendering Context");

		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
			default:
				SLN_ASSERT(false, "Unknown RenderingAPI!");
				return nullptr;
		}
	}
}