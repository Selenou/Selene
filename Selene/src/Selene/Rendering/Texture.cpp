#include "slnpch.h"
#include "Texture.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLTexture.h"

namespace Selene
{
	std::shared_ptr<Texture> Texture::Create(const std::string& path)
	{
		std::string fullPath = "assets/textures/";
		fullPath += path;

		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ENGINE_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture>(fullPath);
			case RenderingAPI::API::Vulkan:
				SLN_ENGINE_ASSERT(false, "RenderingAPI::Vulkan is currently not supported!");
				return nullptr;
			default:
				SLN_ENGINE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
		}
	}

	int Texture::CalculateMipMapLevels(uint32_t width, uint32_t height) const
	{
		int mipmapLevels = 1;

		if (Config::MIPMAP_ENABLED)
		{
			// log2(8) = 3 <=> 2^3 = 8 <=> 3 mipmap level if max(w,h) = 8
			mipmapLevels += (int)floor(log2(std::max(width, height))); 
		}

		return mipmapLevels;
	}
}