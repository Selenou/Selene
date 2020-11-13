#include "slnpch.h"
#include "RenderingAPI.h"
#include "Renderers/OpenGL/OpenGLRenderingAPI.h"

namespace Selene
{
	RenderingAPI::API RenderingAPI::s_API = RenderingAPI::API::None;

	std::unique_ptr<RenderingAPI> RenderingAPI::Create()
	{
		SLN_ENGINE_INFO("Creating RenderingAPI");

		switch (s_API)
		{
			case RenderingAPI::API::None:
				SLN_ENGINE_CRITICAL("RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_unique<OpenGLRenderingAPI>();
			case RenderingAPI::API::Vulkan:
				SLN_ENGINE_CRITICAL("RenderingAPI::Vulkan is currently not available!");
				return nullptr;
		}

		SLN_ENGINE_CRITICAL("Unknown RenderingAPI!");
		return nullptr;
	}
}