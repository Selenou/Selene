#include "slnpch.h"
#include "Pipeline.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLPipeline.h"

namespace Selene
{
	std::shared_ptr<Pipeline> Pipeline::Create()
	{
		switch (RenderingEngine::GetAPI())
		{
		case RenderingAPI::API::None:
			SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
			return nullptr;
		case RenderingAPI::API::OpenGL:
			return std::make_shared<OpenGLPipeline>();
		case RenderingAPI::API::Vulkan:
			SLN_ASSERT(false, "RenderingAPI::Vulkan is currently not supported!");
			return nullptr;
		default:
			SLN_ASSERT(false, "Unknown RendereringAPI!");
			return nullptr;
		}
	}
}
