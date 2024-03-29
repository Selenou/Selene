#include "slnpch.h"
#include "RenderingAPI.h"
#include "Renderers/OpenGL/OpenGLRenderingAPI.h"

namespace Selene
{
	std::unique_ptr<RenderingAPI> RenderingAPI::Create()
	{
		SLN_INFO("Initializing Rendering API");

		switch (s_API)
		{
			case RenderingAPI::API::None:
				SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_unique<OpenGLRenderingAPI>();
			default:
				SLN_ASSERT(false, "Unknown RenderingAPI!");
				return nullptr;
		}
	}
}