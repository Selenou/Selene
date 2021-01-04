#include "slnpch.h"
#include "Shader.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLShader.h"

namespace Selene
{
	std::shared_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		SLN_ENGINE_INFO("Creating Shader from [{0}, {1}]", vertexSrc, fragmentSrc);

		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ENGINE_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
			case RenderingAPI::API::Vulkan:
				SLN_ENGINE_ASSERT(false, "RenderingAPI::Vulkan is currently not available!");
				return nullptr;
			default:
				SLN_ENGINE_ASSERT(false, "Unknown RenderingAPI!");
				return nullptr;
		}
	}
}