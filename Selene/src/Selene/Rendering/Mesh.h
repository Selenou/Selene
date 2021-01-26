#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "Buffer.h"
#include "Pipeline.h"
#include "Material.h"

struct aiScene;

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
		uint32_t MaterialIndex;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	enum MeshImportFlags
	{
		JoinIdenticalVertices = 0x2,		// Identifies and joins identical vertex data / Seems to cause issue with some meshes if aiProcess_PreTransformVertices is not used
		PreTransformVertices = 0x100,		// Removes the node graph, useful if there is no animation and if you don't care about local transforms
		FlipUVs = 0x800000					// Flips all UV coordinates along the y-axis and adjusts material settings and bitangents accordingly
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class Mesh
	{
	public:
		Mesh(const std::string& path, uint32_t importFlags = 0);
		Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::shared_ptr<Material>& material);
		~Mesh() = default;
	public: 
		void SetPosition(const glm::vec3& position) { m_Transform = glm::translate(m_Transform, position); } //tmp
	private:
		void Load(uint32_t importFlags);
		void SetupPipeline();
		void ProcessMeshes(const aiScene* scene);
		void ProcessMaterials(const aiScene* scene);
	private:
		std::string m_FilePath;
		std::vector<Submesh> m_Submeshes;

		std::shared_ptr<VertexBuffer> m_Vbo;
		std::shared_ptr<IndexBuffer> m_Ebo;
		std::shared_ptr<Pipeline> m_Pipeline;

		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;

		std::vector<std::shared_ptr<Material>> m_Materials;

		glm::mat4 m_Transform = glm::mat4(1.0f);

		friend class RenderingEngine;
	};
}