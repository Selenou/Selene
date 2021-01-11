#pragma once

#include "Selene/Config.h"

namespace Selene
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
	protected:
		Texture(const std::string& path) : m_Path(path), m_Width(0), m_Height(0), m_MipmapLevels(1){};
		int CalculateMipMapLevels(uint32_t width, uint32_t height) const;
	public:
		static std::shared_ptr<Texture> Create(const std::string& path);
		virtual void Bind(uint32_t slot = 0) const = 0;
	public:
		inline const std::string& GetPath() const { return m_Path; }
		inline const uint32_t GetWidth() const { return m_Width; }
		inline const uint32_t GetHeight() const { return m_Height; }
	protected:
		uint32_t m_Width, m_Height;
		std::string m_Path;
		int m_MipmapLevels;
	};
}