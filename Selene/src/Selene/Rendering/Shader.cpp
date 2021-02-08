#include "slnpch.h"
#include "Shader.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLShader.h"

namespace Selene
{
	std::shared_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
			case RenderingAPI::API::Vulkan:
				SLN_ASSERT(false, "RenderingAPI::Vulkan is currently not available!");
				return nullptr;
			default:
				SLN_ASSERT(false, "Unknown RenderingAPI!");
				return nullptr;
		}
	}

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	void ShaderLibrary::Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		SLN_ASSERT((m_Shaders.find(name) == m_Shaders.end()), "Shader [%s] is already loaded", name);
		m_Shaders[name] = Shader::Create(vertexSrc, fragmentSrc);
		SLN_INFO("Shader [%s] is loaded and cached", name);
	}

	const std::shared_ptr<Shader>& ShaderLibrary::Get(const std::string& name) const
	{
		SLN_ASSERT((m_Shaders.find(name) != m_Shaders.end()), "Shader [%s] is not loaded", name);
		return m_Shaders.at(name);
	}
}