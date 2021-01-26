#include "Chunk.h"
#include "Cube.h"

void Chunk::Generate()
{
	std::vector<Selene::Vertex> vertices;

	for (int i = 0; i < Cube::vertices.size(); i += 5)
	{
		Selene::Vertex vertex;
		vertex.Position = { Cube::vertices[i], Cube::vertices[i + 1] , Cube::vertices[i + 2] };
		vertex.TexCoord = { Cube::vertices[i + 3], Cube::vertices[i + 4] };
		vertices.emplace_back(vertex);
	}

	std::vector<uint32_t> indices;
	indices.assign(Cube::indices.begin(), Cube::indices.end());

	auto& mat = Selene::Material::Create(Selene::RenderingEngine::GetShaderLibrary()->Get("unlit/unlitTexture"));
	mat->Set(0, Selene::TextureCache::Load("assets/meshes/cube/dirt.png"));

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				int idx = i * 16 * 16 + j * 16 + k;
				m_Mesh[idx] = std::make_shared<Selene::Mesh>("cube", vertices, indices, mat);
				m_Mesh[idx]->SetPosition({ i, j, k });
			}
		}
	}
}

void Chunk::Render()
{
	for (int i = 0; i < m_Mesh.size(); i++)
	{
		Selene::RenderingEngine::SubmitMesh(m_Mesh[i]);
	}
}