#include "slnpch.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Selene
{
	Mesh::Mesh(const std::string& path) :
		m_FilePath(path)
	{
		Load();

		m_Vbo = VertexBuffer::Create(m_Vertices.data(), (uint32_t)(m_Vertices.size() * sizeof(Vertex)));
		m_Ebo = IndexBuffer::Create(m_Indices.data(), (uint32_t)(m_Indices.size() * sizeof(uint32_t)));

		VertexBufferLayout layout = VertexBufferLayout({ { "a_Position", DataType::Float3 } });
		m_Vbo->SetLayout(layout);

		m_Pipeline = Pipeline::Create();
		m_Pipeline->BindVertexBuffer(m_Vbo);
		m_Pipeline->BindIndexBuffer(m_Ebo);

		m_Shader = m_Shader = Shader::Create("baseDebugColor.vert", "baseDebugColor.frag");
	}

	void Mesh::Load()
	{
		SLN_ENGINE_INFO("Loading mesh from [{0}]", m_FilePath.c_str());
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_FilePath, aiProcessPreset_TargetRealtime_Fast | aiProcess_OptimizeMeshes);

		bool isValid = scene && scene->mRootNode && scene->HasMeshes();
		SLN_ENGINE_ASSERT(isValid, importer.GetErrorString());

		// m_Submeshes : emplace_back() with pre-allocation is the fastest
		m_Submeshes.reserve(scene->mNumMeshes);

		uint32_t vertexCount = 0;
		uint32_t indexCount = 0;

		for (size_t meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
		{
			aiMesh* mesh = scene->mMeshes[meshIndex];

			Submesh& submesh = m_Submeshes.emplace_back();
			submesh.Name = mesh->mName.C_Str();
			submesh.IndexCount = mesh->mNumFaces * 3;
			submesh.BaseVertex = vertexCount;

			// Vertices
			for (size_t i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

				m_Vertices.push_back(vertex);
			}

			// Indices
			for (size_t i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];

				SLN_ENGINE_ASSERT((mesh->mFaces[i].mNumIndices == 3), "Face must have 3 indices");

				for (size_t j = 0; j < face.mNumIndices; j++)
				{
					m_Indices.push_back(face.mIndices[j]);
				}
			}

			vertexCount += mesh->mNumVertices;
			indexCount += submesh.IndexCount;
		}
	}
}