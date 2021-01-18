#pragma once

#include "Shader.h"
#include "Texture.h"

namespace Selene
{
	class Material
	{
	public:
		static std::shared_ptr<Material> Create(const std::shared_ptr<Shader>& shader);
		Material(const std::shared_ptr<Shader>& shader) : m_Shader(shader) {};
		virtual ~Material() = default;
	public:
		void Bind();
		void Set(const uint32_t slot, const std::shared_ptr<Texture>& texture);
	public:
		std::shared_ptr<Shader> GetShader() { return m_Shader; }
	private:
		std::shared_ptr<Shader> m_Shader;
		std::vector<std::shared_ptr<Texture>> m_Textures;
	};
}