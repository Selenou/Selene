#include "slnpch.h"
#include "RenderingContext.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLContext.h"
#include "Renderers/Vulkan/VulkanContext.h"

namespace Selene
{
	std::unique_ptr<RenderingContext> RenderingContext::Create(void* window)
	{
		SLN_INFO("Creating RenderingContext");

		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
			case RenderingAPI::API::Vulkan:
				return std::make_unique<VulkanContext>(static_cast<GLFWwindow*>(window));
			default:
				SLN_ASSERT(false, "Unknown RenderingAPI!");
				return nullptr;
		}
	}
}