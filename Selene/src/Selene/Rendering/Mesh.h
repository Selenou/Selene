#pragma once

#include <glm/glm.hpp>

#include "Buffer.h"
#include "Pipeline.h"

namespace Selene
{

	struct Vertex
	{
		glm::vec3 Position;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	struct Submesh
	{
		std::string Name;
		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;

		std::shared_ptr<VertexBuffer> Vbo;
		std::shared_ptr<IndexBuffer> Ebo;
		std::shared_ptr<Pipeline> Pipeline;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class Mesh
	{
	public:
		Mesh(const std::string& path);
		~Mesh() = default;
	public:
		std::vector<Submesh>& GetSubmeshes () { return m_Submeshes; }
	private:
		void Load();
	private:
		std::string m_FilePath;
		std::vector<Submesh> m_Submeshes;
	};
}