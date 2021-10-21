#include "slnpch.h"
#include "Sprite.h"

#include "RenderingEngine.h"

namespace Selene
{
	Sprite::Sprite(const std::string& path) :
		m_FilePath("assets/textures/" + path)
	{
		m_Material = Material::Create(RenderingEngine::GetShaderLibrary()->Get("unlit/unlitTexture"));
		auto&& texture = TextureCache::LoadTexture2D(m_FilePath);
		m_SpriteSize = std::make_pair(texture.get()->GetWidth(), texture.get()->GetHeight());
		m_Material->Set(0, TextureCache::LoadTexture2D(m_FilePath));
		
		SetupPipeline();
	}

	void Sprite::SetupPipeline()
	{
		float halfWidth = m_SpriteSize.first / 2.0f;
		float halfHeight = m_SpriteSize.second / 2.0f;

		std::vector<float> vertices =
		{ 
			-1.0f * halfWidth , -1.0f * halfHeight, 0.0f, 0.0f, 0.0f,
			1.0f * halfWidth, -1.0f * halfHeight, 0.0f, 1.0f, 0.0f,
			1.0f * halfWidth,  1.0f * halfHeight, 0.0f, 1.0f, 1.0f,
			-1.0f * halfWidth, 1.0f * halfHeight, 0.0f, 0.0f, 1.0f
		};

		std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};

		m_Vbo = VertexBuffer::Create(vertices.data(), (uint32_t)(5 * 4 * sizeof(float)));
		m_Ebo = IndexBuffer::Create(indices.data(), (uint32_t)(6 * sizeof(uint32_t)));

		VertexBufferLayout layout = VertexBufferLayout({
			{ "a_Position", DataType::Float3 },
			{ "a_TexCoord", DataType::Float2 }
		});

		m_Vbo->SetLayout(layout);

		m_Pipeline = Pipeline::Create();
		m_Pipeline->BindVertexBuffer(m_Vbo);
		m_Pipeline->BindIndexBuffer(m_Ebo);
	}
}