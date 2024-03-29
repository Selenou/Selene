#include "slnpch.h"
#include "Texture.h"
#include "RenderingEngine.h"
#include "Renderers/OpenGL/OpenGLTexture.h"

namespace Selene
{
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

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture2D>(path);
			default:
				SLN_ASSERT(false, "Unknown RenderingAPI!");
				return nullptr;
		}
	}

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	const std::shared_ptr<Texture>& TextureCache::LoadTexture2D(const std::string& name)
	{
		if (!TextureCache::IsInCache(name))
		{
			TextureCache::Add(name, Texture2D::Create(name));
		}

		return TextureCache::Get(name);
	}

	const std::shared_ptr<Texture>& TextureCache::LoadTextureArray(const std::string& name, int hCount, int vCount)
	{
		if (!TextureCache::IsInCache(name))
		{
			TextureCache::Add(name, TextureArray::Create(name, hCount, vCount));
		}

		return TextureCache::Get(name);
	}

	const std::shared_ptr<Texture>& TextureCache::Get(const std::string& name)
	{
		 return s_TextureCache.at(name);
	}

	bool TextureCache::IsInCache(const std::string& name)
	{
		return s_TextureCache.find(name) != s_TextureCache.end();
	}

	void TextureCache::Add(const std::string& name, const std::shared_ptr<Texture>& texture)
	{
		s_TextureCache.emplace(name, texture); // TODO : we may not want to use strong ref here, std::unordered_map<std::string, const std::shared_ptr<Texture2D>&> or weak_ptr ? Need to investigate
		SLN_INFO("Texture [%s] is added in texture cache", name);
	}

	//void TextureCache::Remove(const std::string& name)
	//{
		//s_TextureCache.erase(name);	
	//}

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	std::shared_ptr<TextureCubeMap> TextureCubeMap::Create(const std::string& path)
	{
		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_shared<OpenGLTextureCubeMap>(path);
			default:
				SLN_ASSERT(false, "Unknown RenderingAPI!");
				return nullptr;
		}
	}

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	std::shared_ptr<TextureArray> TextureArray::Create(const std::string& path, int hCount, int vCount)
	{
		switch (RenderingEngine::GetAPI())
		{
			case RenderingAPI::API::None:
				SLN_ASSERT(false, "RenderingAPI::None is currently not supported!");
				return nullptr;
			case RenderingAPI::API::OpenGL:
				return std::make_shared<OpenGLTextureArray>(path, hCount, vCount);
			default:
				SLN_ASSERT(false, "Unknown RenderingAPI!");
				return nullptr;
		}
	}
}