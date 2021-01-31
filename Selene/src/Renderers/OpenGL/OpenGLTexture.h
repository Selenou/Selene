#pragma once

#include "Selene/Rendering/Texture.h"

namespace Selene
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();
	public:
		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_TextureID; 
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class OpenGLTextureCubeMap : public TextureCubeMap
	{
	public:
		OpenGLTextureCubeMap(const std::string& path);
		virtual ~OpenGLTextureCubeMap();
	public:
		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_TextureID;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class OpenGLTextureArray : public TextureArray
	{
	public:
		OpenGLTextureArray(const std::string& path, int count);
		virtual ~OpenGLTextureArray();
	public:
		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_TextureID;
	};
}