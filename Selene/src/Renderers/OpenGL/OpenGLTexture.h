#pragma once

#include "Selene/Rendering/Texture.h"

namespace Selene
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& fullpath);
		virtual ~OpenGLTexture();
	public:
		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_TextureID; 
	};
}