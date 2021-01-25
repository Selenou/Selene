#include "slnpch.h"
#include "Mesh.h"

#include "RenderingEngine.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

namespace Selene
{
	static const uint32_t s_BaseImportFlags =
		aiProcess_Triangulate |				// Make sure we use triangles
		aiProcess_GenNormals |				// Create normals
		aiProcess_CalcTangentSpace |		// Create binormals/tangents
		aiProcess_GenUVCoords |				// Convert UVs if required 
		aiProcess_SortByPType |				// Split meshes by primitive type
		aiProcess_OptimizeMeshes |			// Batch draws where possible
		aiProcess_RemoveRedundantMaterials;	// Remove useless materials  			


	Mesh::Mesh(const std::string& path, uint32_t flags) :
		m_FilePath("assets/meshes/" + path)
	{
		uint32_t importFlags = s_BaseImportFlags | flags;

		Load(importFlags);
		SetupPipeline();
	}

	void Mesh::Load(uint32_t importFlags)
	{
		SLN_ENGINE_INFO("Loading mesh from [{0}]", m_FilePath.c_str());

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_FilePath, importFlags);

		bool isValid = scene && scene->mRootNode && scene->HasMeshes();
		SLN_ENGINE_ASSERT(isValid, importer.GetErrorString());

		ProcessMeshes(scene);
		ProcessMaterials(scene);
	}

	void Mesh::SetupPipeline()
	{
		m_Vbo = VertexBuffer::Create(m_Vertices.data(), (uint32_t)(m_Vertices.size() * sizeof(Vertex)));
		m_Ebo = IndexBuffer::Create(m_Indices.data(), (uint32_t)(m_Indices.size() * sizeof(uint32_t)));

		VertexBufferLayout layout = VertexBufferLayout({
			{ "a_Position", DataType::Float3 },
			{ "a_TexCoord", DataType::Float2 }
		});

		m_Vbo->SetLayout(layout);

		m_Pipeline = Pipeline::Create();
		m_Pipeline->BindVertexBuffer(m_Vbo);
		m_Pipeline->BindIndexBuffer(m_Ebo);
	}

	void Mesh::ProcessMeshes(const aiScene* scene)
	{
		uint32_t vertexCount = 0;
		uint32_t indexCount = 0;

		// m_Submeshes : emplace_back() with pre-allocation is the fastest
		m_Submeshes.reserve(scene->mNumMeshes);

		for (size_t meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
		{
			aiMesh* mesh = scene->mMeshes[meshIndex];

			Submesh& submesh = m_Submeshes.emplace_back();
			submesh.Name = mesh->mName.C_Str();
			submesh.IndexCount = mesh->mNumFaces * 3;
			submesh.BaseVertex = vertexCount;
			submesh.MaterialIndex = mesh->mMaterialIndex;

			// Vertices
			for (size_t i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

				if (mesh->HasTextureCoords(0))
				{
					vertex.TexCoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
				}

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

	void Mesh::ProcessMaterials(const aiScene* scene)
	{
		if (scene->HasMaterials())
		{
			m_Materials.resize(scene->mNumMaterials);

			for (uint32_t i = 0; i < scene->mNumMaterials; i++)
			{
				auto aiMaterial = scene->mMaterials[i];
				auto aiMaterialName = aiMaterial->GetName();
				//SLN_ENGINE_TRACE("Processing material [{0}]", aiMaterialName.data);

				auto& mat = Material::Create(RenderingEngine::GetShaderLibrary()->Get("unlit/unlitTexture"));
				
				aiString aiTexPath;

				bool hasAlbedoMap = aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexPath) == AI_SUCCESS;

				if (hasAlbedoMap)
				{
					std::filesystem::path path = m_FilePath;
					auto parentPath = path.parent_path();
					parentPath /= std::string(aiTexPath.data); // concatenation for path

					mat->Set(0, TextureCache::Load(parentPath.string()));
				}

				m_Materials[i] = mat;
			}
		}
	}
}