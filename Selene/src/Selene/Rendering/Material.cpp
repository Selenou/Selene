#include "slnpch.h"
#include "Material.h"

namespace Selene
{
	std::shared_ptr<Material> Material::Create(const std::shared_ptr<Shader>& shader)
	{
		return std::make_shared<Material>(shader);
	}

	void Material::Bind()
	{
		m_Shader->Bind();

		for (uint32_t i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i]->Bind(i);
		}
	}

	void Material::Set(const uint32_t slot, const std::shared_ptr<Texture>& texture)
	{
		if (m_Textures.size() <= slot)
			m_Textures.resize((size_t)slot + 1);

		m_Textures[slot] = texture;
	}
}