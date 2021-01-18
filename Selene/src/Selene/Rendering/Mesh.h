#pragma once

#include <glm/glm.hpp>

#include "Buffer.h"
#include "Pipeline.h"
#include "Shader.h"
#include "Texture.h"

namespace Selene
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	struct Submesh
	{
		std::string Name;
		uint32_t IndexCount;
		uint32_t BaseVertex;
		//uint32_t MaterialIndex;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class Mesh
	{
	public:
		Mesh(const std::string& path);
		~Mesh() = default;
	private:
		void Load();
	private:
		std::string m_FilePath;
		std::vector<Submesh> m_Submeshes;

		std::shared_ptr<VertexBuffer> m_Vbo;
		std::shared_ptr<IndexBuffer> m_Ebo;
		std::shared_ptr<Pipeline> m_Pipeline;

		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;

		// TODO : material
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture2D> m_Texture;

		glm::mat4 m_Transform = glm::mat4(1.0f);

		friend class RenderingEngine;
	};
}