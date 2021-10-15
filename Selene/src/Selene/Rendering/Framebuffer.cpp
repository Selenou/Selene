#include "slnpch.h"
#include "Framebuffer.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLFramebuffer.h"

namespace Selene
{
	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecs& spec)
	{
		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_shared<OpenGLFramebuffer>(spec);
			default:
				SLN_ASSERT(false, "Unknown RendereringAPI!");
				return nullptr;
		}
	}
}