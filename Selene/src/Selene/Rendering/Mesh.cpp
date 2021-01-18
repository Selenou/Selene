#include "slnpch.h"
#include "Mesh.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include "glm/gtc/matrix_transform.hpp"

namespace Selene
{
	Mesh::Mesh(const std::string& path) :
		m_FilePath("assets/meshes/" + path)
	{
		Load();

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

		m_Shader = m_Shader = Shader::Create("unlit/unlitTexture.vert", "unlit/unlitTexture.frag");
		m_Texture = Texture2D::Create("test/corgi.jpg");
		m_Transform = glm::rotate(glm::mat4(1.0f), glm::radians(-70.0f), glm::vec3(1, 0, 0));
		m_Transform = glm::rotate(m_Transform, glm::radians(30.0f), glm::vec3(0, 1, 0));
	}

	void Mesh::Load()
	{
		SLN_ENGINE_INFO("Loading mesh from [{0}]", m_FilePath.c_str());
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_FilePath, 
			 aiProcess_Triangulate |				// Make sure we use triangles
			 aiProcess_GenNormals |					// Make sure we have legit normals
			 aiProcess_OptimizeMeshes |				// Batch draws where possible
			 aiProcess_SortByPType |				// Split meshes by primitive type
			 aiProcess_CalcTangentSpace	|			// Create binormals/tangents
			 aiProcess_GenUVCoords |				// Convert UVs if required 
			 aiProcess_JoinIdenticalVertices //|		// Identifies and joins identical vertex data / Seems to cause issue with backpack.obj if aiProcess_PreTransformVertices is not used
			 //aiProcess_FlipUVs |					// Because in OpenGLTexture : stbi_set_flip_vertically_on_load(1); This can be remove if we remove stbi_set_flip_vertically_on_load(1)
			// | aiProcess_PreTransformVertices		// Removes the node graph, useful if there is no animation and if you don't care about local transforms
		);

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
			//submesh.MaterialIndex = mesh->mMaterialIndex;

			// Vertices
			for (size_t i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
				
				if (mesh->HasTextureCoords(0))
					vertex.TexCoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };

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
			SLN_ENGINE_TRACE(vertexCount);
		}

		/*
		if (scene->HasMaterials())
		{
			SLN_ENGINE_TRACE(scene->mNumMaterials);

			for (uint32_t i = 0; i < scene->mNumMaterials; i++)
			{
				auto aiMaterial = scene->mMaterials[i];
				auto aiMaterialName = aiMaterial->GetName();
				SLN_ENGINE_TRACE(aiMaterialName.data);
			}
		}
		*/
	}
}