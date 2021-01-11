#include "slnpch.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include "stb_image.h"

namespace Selene
{
	OpenGLTexture::OpenGLTexture(const std::string& fullpath)
		: Texture(fullpath)
	{
		// Load image
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(fullpath.c_str(), &width, &height, &channels, 0);
		SLN_ENGINE_INFO("Loading image from [{0}] : width:{1}, height:{2}, channels:{3}", fullpath, width, height, channels);
		m_Width = width;
		m_Height = height;

		// Check img format
		GLenum internalFormat = GL_NONE;
		GLenum dataFormat = GL_NONE;

		if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
			// if texture width is not a multiple of 4, we need to add this
			// since the alignemenent must be a divisor or width * channels (default is 4)
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		}
		else if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}

		// Create texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		m_MipmapLevels = CalculateMipMapLevels(width, height);
		glTextureStorage2D(m_TextureID, m_MipmapLevels, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, m_MipmapLevels == 1 ? GL_LINEAR : GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		// Generate Mipmap if needed
		if (m_MipmapLevels > 1)
		{
			glGenerateTextureMipmap(m_TextureID);
		}

		// Restore pixel alignment
		if (channels == 3)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}

		// Release resource
		stbi_image_free(data);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTexture::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_TextureID);
	}
}