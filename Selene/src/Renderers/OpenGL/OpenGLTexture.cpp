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
		SLN_ENGINE_INFO("Loading image from [{0}]", fullpath);
		stbi_uc* data = stbi_load(fullpath.c_str(), &width, &height, &channels, 0);
		SLN_ENGINE_INFO("Loaded ! : width:{0}, height:{1}, channels:{2}", width, height, channels);
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
		SLN_ENGINE_INFO("Loading image from [{0}]", fullpath);
		stbi_uc* data = data = stbi_load(fullpath.c_str(), &width, &height, &channels, 0);
		SLN_ENGINE_INFO("Loaded ! : width:{0}, height:{1}, channels:{2}", width, height, channels);

		m_Width = width;
		m_Height = height;
		uint32_t faceWidth = m_Width / 4;
		uint32_t faceHeight = m_Height / 3;

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

		glTextureStorage2D(m_TextureID, 1, internalFormat, faceWidth, faceHeight);

		std::array<stbi_uc*, 6> faces;
		for (size_t i = 0; i < faces.size(); i++)
		{
			faces[i] = new uint8_t[faceWidth * faceHeight * channels];
		}

		GLint faceIndex = 0;

		// H loop
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t y = 0; y < faceHeight; y++)
			{
				size_t yOffset = y + faceHeight;
				for (size_t x = 0; x < faceWidth; x++)
				{
					size_t xOffset = x + i * faceWidth;
					for (int j = 0; j < channels; j++)
					{
						faces[faceIndex][(x + y * faceWidth) * channels + j] = data[(xOffset + yOffset * m_Width) * channels + j];
					}
				}
			}
			faceIndex++;
		}

		// V loop
		for (size_t i = 0; i < 3; i++)
		{
			if (i == 1)
				continue;

			for (size_t y = 0; y < faceHeight; y++)
			{
				size_t yOffset = y + i * faceHeight;
				for (size_t x = 0; x < faceWidth; x++)
				{
					size_t xOffset = x + faceWidth;
					for (int j = 0; j < channels; j++)
					{
						faces[faceIndex][(x + y * faceWidth) * channels + j] = data[(xOffset + yOffset * m_Width) * channels + j];
					}
				}
			}
			faceIndex++;
		}

		/*
		GL_TEXTURE_CUBE_MAP_POSITIVE_X	0	Right	faces[2]
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X	1	Left	faces[0]
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y	2	Top		faces[4]
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y	3	Bottom	faces[5]
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z	4	Back	faces[1]
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z	5	Front	faces[3]
		*/

		glTextureSubImage3D(m_TextureID, 0, 0, 0, 0, faceWidth, faceHeight, 1, dataFormat, GL_UNSIGNED_BYTE, faces[2]);
		glTextureSubImage3D(m_TextureID, 0, 0, 0, 1, faceWidth, faceHeight, 1, dataFormat, GL_UNSIGNED_BYTE, faces[0]);
		glTextureSubImage3D(m_TextureID, 0, 0, 0, 2, faceWidth, faceHeight, 1, dataFormat, GL_UNSIGNED_BYTE, faces[4]);
		glTextureSubImage3D(m_TextureID, 0, 0, 0, 3, faceWidth, faceHeight, 1, dataFormat, GL_UNSIGNED_BYTE, faces[5]);
		glTextureSubImage3D(m_TextureID, 0, 0, 0, 4, faceWidth, faceHeight, 1, dataFormat, GL_UNSIGNED_BYTE, faces[1]);
		glTextureSubImage3D(m_TextureID, 0, 0, 0, 5, faceWidth, faceHeight, 1, dataFormat, GL_UNSIGNED_BYTE, faces[3]);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		if (channels == 3)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}

		stbi_image_free(data);
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