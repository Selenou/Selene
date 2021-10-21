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
		m_Material->Set(0, texture);

		m_SpriteSize = std::make_pair(texture->GetWidth(), texture->GetHeight());
		m_TextureCoords = { glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) };

		SetupPipeline();
	}

	Sprite::Sprite(const std::string& path, int x, int y, uint32_t w, uint32_t h, bool flipY) :
		m_FilePath("assets/textures/" + path)
	{
		m_Material = Material::Create(RenderingEngine::GetShaderLibrary()->Get("unlit/unlitTexture"));
		auto&& texture = TextureCache::LoadTexture2D(m_FilePath);
		m_Material->Set(0, texture);

		m_SpriteSize = std::make_pair(w, h);

		glm::vec2 min = { x / (float)texture->GetWidth(), 1.0f - (y / (float)texture->GetHeight()) };
		glm::vec2 max = { (x + w) / (float)texture->GetWidth(), 1.0f - ((y + h) / (float)texture->GetHeight()) };

		m_TextureCoords[0] = { min.x, flipY ? max.y : min.y };
		m_TextureCoords[1] = { max.x, flipY ? max.y : min.y };
		m_TextureCoords[2] = { max.x, flipY ? min.y : max.y };
		m_TextureCoords[3] = { min.x, flipY ? min.y : max.y };

 		SetupPipeline();
	}

	void Sprite::SetupPipeline()
	{
		std::vector<float> vertices =
		{ 
			-0.5f * m_SpriteSize.first , -0.5f * m_SpriteSize.second, 0.0f, m_TextureCoords[0][0], m_TextureCoords[0][1],
			0.5f * m_SpriteSize.first, -0.5f * m_SpriteSize.second, 0.0f, m_TextureCoords[1][0], m_TextureCoords[1][1],
			0.5f * m_SpriteSize.first, 0.5f * m_SpriteSize.second, 0.0f, m_TextureCoords[2][0], m_TextureCoords[2][1],
			-0.5f * m_SpriteSize.first, 0.5f * m_SpriteSize.second, 0.0f, m_TextureCoords[3][0], m_TextureCoords[3][1]
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