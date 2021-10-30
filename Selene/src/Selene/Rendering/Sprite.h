#pragma once

#include "Buffer.h"
#include "Pipeline.h"
#include "Material.h"

namespace Selene
{
	class Sprite
	{
	public:
		Sprite(const std::string& path);
		Sprite(const std::string& path, int x, int y, uint32_t w, uint32_t h, bool flipY = false);
		~Sprite() = default;
	private:
		void SetupPipeline();
	private:
		std::string m_FilePath;
		std::shared_ptr<VertexBuffer> m_Vbo;
		std::shared_ptr<IndexBuffer> m_Ebo;
		std::shared_ptr<Pipeline> m_Pipeline;
		std::shared_ptr<Material> m_Material;
		std::pair<uint32_t, uint32_t> m_SpriteSize;

		std::array<glm::vec2, 4> m_TextureCoords;

		friend class RenderingEngine;
	};
}