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

		for (size_t meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
		{
			aiMesh* mesh = scene->mMeshes[meshIndex];

			Submesh& submesh = m_Submeshes.emplace_back();
			submesh.Name = mesh->mName.C_Str(); 
			
			// Vertices
			for (size_t i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

				submesh.Vertices.push_back(vertex);
			}

			// Indices
			for (size_t i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];

				SLN_ENGINE_ASSERT((mesh->mFaces[i].mNumIndices == 3), "Face must have 3 indices");
				for (size_t j = 0; j < face.mNumIndices; j++)
				{
					submesh.Indices.push_back(face.mIndices[j]);
				}
			}

			submesh.Vbo = VertexBuffer::Create(submesh.Vertices.data(), (uint32_t)(submesh.Vertices.size() * sizeof(Vertex)));
			submesh.Ebo = IndexBuffer::Create(submesh.Indices.data(), (uint32_t)(submesh.Indices.size() * sizeof(uint32_t)));

			VertexBufferLayout layout = VertexBufferLayout({ { "a_Position", DataType::Float3 } });
			submesh.Vbo->SetLayout(layout);

			submesh.Pipeline = Pipeline::Create();
			submesh.Pipeline->SetVertexBuffer(submesh.Vbo);
			submesh.Pipeline->SetIndexBuffer(submesh.Ebo);
		}
	}
}