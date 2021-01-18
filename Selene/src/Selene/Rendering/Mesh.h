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

	enum MeshImportFlags
	{
		FlipUVs = 0x01,					// Flips all UV coordinates along the y-axis and adjusts material settings and bitangents accordingly
		JoinIdenticalVertices = 0x02,	// Identifies and joins identical vertex data / Seems to cause issue with some meshes if aiProcess_PreTransformVertices is not used
		PreTransformVertices = 0x04		// Removes the node graph, useful if there is no animation and if you don't care about local transforms
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class Mesh
	{
	public:
		Mesh(const std::string& path, uint32_t importFlags = 0);
		~Mesh() = default;
	private:
		void Load(uint32_t importFlags);
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