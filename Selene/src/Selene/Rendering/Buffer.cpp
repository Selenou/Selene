#include "slnpch.h"
#include "Buffer.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLBuffer.h"

namespace Selene
{
	VertexBufferLayout::VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements)
		: m_Elements(elements)
	{
		ComputeLayoutStride();
		ComputeElementsOffset();
	}

	void VertexBufferLayout::ComputeLayoutStride()
	{
		for (auto& element : m_Elements)
		{
			m_Stride += element.Size;
		}
	}

	void VertexBufferLayout::ComputeElementsOffset()
	{
		uint32_t offset = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
		}
	}

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size)
	{
		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexBuffer>(data, size);
			case RenderingAPI::API::Vulkan:
				SLN_ASSERT(false, "RenderingAPI::Vulkan is currently not supported!");
				return nullptr;
			default:
				SLN_ASSERT(false, "Unknown RendereringAPI!");
				return nullptr;
		}
	}

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
	{
		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_shared<OpenGLIndexBuffer>(data, size);
			case RenderingAPI::API::Vulkan:
				SLN_ASSERT(false, "RenderingAPI::Vulkan is currently not supported!");
				return nullptr;
			default:
				SLN_ASSERT(false, "Unknown RendereringAPI!");
				return nullptr;
		}
	}
}