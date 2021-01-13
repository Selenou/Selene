#include "slnpch.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include "stb_image.h"

namespace Selene
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& fullpath)
		: Texture2D(fullpath)
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

		stbi_set_flip_vertically_on_load(0);

		// Release resource
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_TextureID);
	}

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	OpenGLTextureCubeMap::OpenGLTextureCubeMap(const std::string& fullpath) 
		: TextureCubeMap(fullpath)
	{
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_TextureID);
		int width, height, channels;
		stbi_uc* data;
		for (int faceIndex = 0; faceIndex < 6; faceIndex++)
		{
			std::string path = fullpath;
			path += std::to_string(faceIndex);
			path += ".jpg";

			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
			SLN_ENGINE_INFO("Loading image from [{0}] : width:{1}, height:{2}, channels:{3}", path, width, height, channels);

			// Use first face index to set texture storage parameters
			if (!faceIndex) 
			{
				glTextureStorage2D(m_TextureID, 1, GL_RGBA8, width, height);
			}

			glTextureSubImage3D(m_TextureID, 0, 0, 0, faceIndex, width, height, 1, GL_RGB, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	OpenGLTextureCubeMap::~OpenGLTextureCubeMap()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTextureCubeMap::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_TextureID);
	}
}