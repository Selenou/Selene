#include "slnpch.h"
#include "RenderingPipeline.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLPipeline.h"

namespace Selene
{
	std::shared_ptr<RenderingPipeline> RenderingPipeline::Create(const VertexBufferLayout& layout)
	{
		switch (RenderingEngine::GetAPI())
		{
		case RenderingAPI::API::None:
			SLN_ENGINE_ASSERT(false, "RenderingAPI::None is currently not supported!");
			return nullptr;
		case RenderingAPI::API::OpenGL:
			return std::make_shared<OpenGLPipeline>(layout);
		case RenderingAPI::API::Vulkan:
			SLN_ENGINE_ASSERT(false, "RenderingAPI::Vulkan is currently not supported!");
			return nullptr;
		default:
			SLN_ENGINE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}
