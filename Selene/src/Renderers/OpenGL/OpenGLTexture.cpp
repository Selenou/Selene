#include "slnpch.h"
#include "OpenGLTexture.h"
#include "Selene/Config.h"
#include <glad/glad.h>
#include <stb_image.h>

namespace Selene
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: Texture2D(path)
	{
		// Load image
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);

		SLN_INFO("Loading image from [%s]", path);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		SLN_ASSERT(data, "Failed to load image");

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

		if (Config::TEXTURE_FILTERING_ENABLED)
			glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, m_MipmapLevels == 1 ? GL_LINEAR : GL_LINEAR_MIPMAP_LINEAR);
		else
			glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, m_MipmapLevels == 1 ? GL_NEAREST : GL_NEAREST_MIPMAP_LINEAR);
			
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, Config::TEXTURE_FILTERING_ENABLED ? GL_LINEAR : GL_NEAREST);
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

	OpenGLTextureCubeMap::OpenGLTextureCubeMap(const std::string& path) 
		: TextureCubeMap(path)
	{
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_TextureID);

		int width, height, channels;

		SLN_INFO("Loading image from [%s]", path);
		stbi_uc* data = data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		SLN_ASSERT(data, "Failed to load image");

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

		for (size_t i = 0; i < faces.size(); i++)
		{
			delete[] faces[i];
		}
	}

	OpenGLTextureCubeMap::~OpenGLTextureCubeMap()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTextureCubeMap::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_TextureID);
	}

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	OpenGLTextureArray::OpenGLTextureArray(const std::string& path, int hCount, int vCount)
		: TextureArray(path, hCount, vCount)
	{
		glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_TextureID);

		int width, height, channels;

		SLN_INFO("Loading image from [%s]", path);
		stbi_uc* data = data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		SLN_ASSERT(data, "Failed to load image");

		m_Width = width;
		m_Height = height;

		m_TileWidth = m_Width / hCount;
		m_TileHeight = m_Height / vCount;

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

		m_MipmapLevels = CalculateMipMapLevels(m_TileWidth, m_TileHeight);


		glTextureStorage3D(m_TextureID, m_MipmapLevels, internalFormat, m_TileWidth, m_TileHeight, hCount * vCount);

		int rowLength = hCount * m_TileWidth * channels;
		std::vector<stbi_uc> tileData(m_TileWidth * m_TileHeight * channels);

		for (int i = 0; i < vCount; i++)
		{
			for (int j = 0; j < hCount; j++)
			{
				stbi_uc* ptr = data + (i * rowLength * m_TileHeight) + (j * m_TileHeight * channels);

				for (uint32_t row = 0; row < m_TileHeight; row++)
				{
					auto ptrStart = ptr + (row * rowLength);
					auto ptrEnd = ptrStart + (m_TileWidth * channels);
					auto dest = tileData.begin() + row * (m_TileWidth * channels);

					std::copy(ptrStart, ptrEnd, dest);
				}

				int zOffset = i * hCount + j;
				glTextureSubImage3D(m_TextureID, 0, 0, 0, zOffset, m_TileWidth, m_TileHeight, 1, dataFormat, GL_UNSIGNED_BYTE, tileData.data());
			}
		}

		/*
		GL_NEAREST					= no filtering at all
		GL_NEAREST_MIPMAP_LINEAR	= linear filtering between mipmap levels, but no filtering inside each mipmap level
		GL_NEAREST_MIPMAP_NEAREST	= no filtering, but mipmap selection
		GL_LINEAR_MIPMAP_NEAREST	= bilinear filtering, with mipmap selection
		GL_LINEAR_MIPMAP_LINEAR		= trilinear filtering
		*/
		if (Config::TEXTURE_FILTERING_ENABLED)
			glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, m_MipmapLevels == 1 ? GL_LINEAR : GL_LINEAR_MIPMAP_LINEAR);
		else
			glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, m_MipmapLevels == 1 ? GL_NEAREST : GL_NEAREST_MIPMAP_LINEAR);
			
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, Config::TEXTURE_FILTERING_ENABLED ? GL_LINEAR : GL_NEAREST);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if (m_MipmapLevels > 1)
		{
			glGenerateTextureMipmap(m_TextureID);
		}
		if (channels == 3)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}

		stbi_image_free(data);
	}

	OpenGLTextureArray::~OpenGLTextureArray()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTextureArray::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_TextureID);
	}
}