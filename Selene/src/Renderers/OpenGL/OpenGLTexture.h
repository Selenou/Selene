#pragma once

#include "Selene/Rendering/Texture.h"

namespace Selene
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& fullpath);
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
		OpenGLTextureCubeMap(const std::string& fullpath);
		virtual ~OpenGLTextureCubeMap();
	public:
		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_TextureID;
	};
}