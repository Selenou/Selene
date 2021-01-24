#pragma once

#include "Selene/Config.h"

namespace Selene
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
	protected:
		Texture(const std::string& path) : m_Path(path), m_Width(0), m_Height(0) {};
	public:
		virtual void Bind(uint32_t slot = 0) const = 0;
	public:
		inline const std::string& GetPath() const { return m_Path; }
		inline const uint32_t GetWidth() const { return m_Width; }
		inline const uint32_t GetHeight() const { return m_Height; }
	protected:
		uint32_t m_Width, m_Height;
		std::string m_Path;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class Texture2D : public Texture
	{
	public:
		static std::shared_ptr<Texture2D> Create(const std::string& path);
	protected:
		Texture2D(const std::string& path) : Texture(path), m_MipmapLevels(1) {};
		int CalculateMipMapLevels(uint32_t width, uint32_t height) const;
	protected:
		int m_MipmapLevels;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class TextureCache // TODO : Make a Resource Manager instead
	{
	public:
		static const std::shared_ptr<Texture2D>& Load(const std::string& name);
		static const std::shared_ptr<Texture2D>& Get(const std::string& name);
		static bool IsInCache(const std::string& name);
		static void Add(const std::string& name, const std::shared_ptr<Texture2D>& texture);
		static void Remove(const std::string& name);
	private:
		static std::unordered_map<std::string, std::shared_ptr<Texture2D>> s_TextureCache;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class TextureCubeMap : public Texture
	{
	public:
		static std::shared_ptr<TextureCubeMap> Create(const std::string& path);
	protected:
		TextureCubeMap(const std::string& path) : Texture(path) {};
	};
}