#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Buffer.h"
#include "Pipeline.h"
#include "Material.h"

namespace Selene
{
	class Sprite
	{
	public:
		Sprite(const std::string& path);
		~Sprite() = default;
	public:
		void SetPosition(const glm::vec3& position) { m_Transform = glm::translate(m_Transform, position); }
		void SetScale(const glm::vec3& scale) { m_Transform = glm::scale(m_Transform, scale); }
	private:
		void SetupPipeline();
	private:
		std::string m_FilePath;

		std::shared_ptr<VertexBuffer> m_Vbo;
		std::shared_ptr<IndexBuffer> m_Ebo;
		std::shared_ptr<Pipeline> m_Pipeline;

		std::shared_ptr<Material> m_Material;

		std::pair<uint32_t, uint32_t> m_SpriteSize;

		glm::mat4 m_Transform = glm::mat4(1.0f);

		friend class RenderingEngine;
	};
}