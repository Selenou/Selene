#include "slnpch.h"
#include "RenderingContext.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLContext.h"

namespace Selene
{
	std::unique_ptr<RenderingContext> RenderingContext::Create(void* window)
	{
		SLN_ENGINE_INFO("Creating RenderingContext");

		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ENGINE_CRITICAL("RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
			case RenderingAPI::API::Vulkan:
				SLN_ENGINE_CRITICAL("RenderingAPI::Vulkan is currently not available!");
				return nullptr;
		}

		SLN_ENGINE_CRITICAL("Unknown RenderingAPI!");
		return nullptr;
	}
}