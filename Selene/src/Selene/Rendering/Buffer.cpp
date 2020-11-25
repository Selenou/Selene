#include "slnpch.h"
#include "Buffer.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLBuffer.h"

namespace Selene
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size)
	{
		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ENGINE_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexBuffer>(data, size);
			case RenderingAPI::API::Vulkan:
				SLN_ENGINE_ASSERT(false, "RenderingAPI::Vulkan is currently not supported!");
				return nullptr;
		}

		SLN_ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	std::shared_ptr<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
	{
		switch (RenderingEngine::GetAPI())
		{
		case RenderingAPI::API::None:
			SLN_ENGINE_ASSERT(false, "RenderingAPI::None is currently not supported!");
			return nullptr;
		case RenderingAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(data, size);
		case RenderingAPI::API::Vulkan:
			SLN_ENGINE_ASSERT(false, "RenderingAPI::Vulkan is currently not supported!");
			return nullptr;
		}

		SLN_ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}