#include "Chunk.h"
#include <memory>

namespace Sandbox
{
	Chunk::Chunk(int x, int y) 
		: m_ChunkOffsetX(x * WorldConfig::CHUNK_SIZE), m_ChunkOffsetY(y * WorldConfig::CHUNK_SIZE)
	{
		FillChunk(BlockType::Dirt);
	}

	void Chunk::GenerateMesh()
	{
		std::vector<Selene::Vertex> vertices;
		std::vector<uint32_t> indices;

		int tmpCount = 0;

		for (int x = 0; x < WorldConfig::CHUNK_SIZE; x++)
		{
			for (int y = 0; y < WorldConfig::CHUNK_HEIGHT; y++)
			{
				for (int z = 0; z < WorldConfig::CHUNK_SIZE; z++)
				{
					Block block = m_Blocks[x][y][z];

					if (block.BlockType != BlockType::Air)
					{
						if (IsBlockVisible(x, y, z))
						{
							for (int i = 0; i < BlockFaces::FrontFaceVertices.size(); i+=5)
							{
								Selene::Vertex vertex;
								vertex.Position = { BlockFaces::FrontFaceVertices[i] + x, BlockFaces::FrontFaceVertices[i + 1] - y , BlockFaces::FrontFaceVertices[i + 2] + z};
								vertex.TexCoord = { BlockFaces::FrontFaceVertices[i + 3], BlockFaces::FrontFaceVertices[i + 4] };
								vertices.emplace_back(vertex);
							}

							for (int i = 0; i < 36; i++)
							{
								indices.push_back(tmpCount);
								tmpCount++;
							}
						}
					}
				}
			}
		}

		auto& mat = Selene::Material::Create(Selene::RenderingEngine::GetShaderLibrary()->Get("chunk"));
		mat->Set(0, Selene::TextureCache::Load("assets/meshes/cube/dirt.png"));

		m_Mesh = std::make_shared<Selene::Mesh>("block", vertices, indices, mat);
		m_Mesh->SetPosition({ m_ChunkOffsetX, 0.0f, m_ChunkOffsetY }); // y is up
	}

	void Chunk::Render()
	{
		Selene::RenderingEngine::SubmitMesh(m_Mesh);
	}

	void Chunk::SetNeighbors(std::array<std::shared_ptr<Chunk>, 4> neighbors)
	{
		for (int i = 0; i < 4; i++)
		{
			m_ChunkNeighbors[i] = neighbors[i];
		}
	}

	void Chunk::FillChunk(BlockType type)
	{
		for (int x = 0; x < WorldConfig::CHUNK_SIZE; x++)
		{
			for (int y = 0; y < WorldConfig::CHUNK_HEIGHT; y++)
			{
				for (int z = 0; z < WorldConfig::CHUNK_SIZE; z++)
				{
					m_Blocks[x][y][z] = { type };
				}
			}
		}
	}

	std::array<Block*, 6> Chunk::GetBlockNeighbors(int x, int y, int z)
	{
		const int min = 0;
		const int maxSize = WorldConfig::CHUNK_SIZE - 1;
		const int maxHeight = WorldConfig::CHUNK_HEIGHT - 1;

		std::array<Block*, 6> blockNeighbors;
		blockNeighbors[Direction::Left]		= x > min		? &m_Blocks[x-1][y][z] : m_ChunkNeighbors[Direction::Left].lock().get() ? m_ChunkNeighbors[Direction::Left].lock().get()->GetBlock(maxSize, y, z) : nullptr;
		blockNeighbors[Direction::Right]	= x < maxSize	? &m_Blocks[x+1][y][z] : m_ChunkNeighbors[Direction::Right].lock().get() ? m_ChunkNeighbors[Direction::Right].lock().get()->GetBlock(min, y, z) : nullptr;
		blockNeighbors[Direction::Front]	= z < maxSize	? &m_Blocks[x][y][z+1] : m_ChunkNeighbors[Direction::Front].lock().get() ? m_ChunkNeighbors[Direction::Front].lock().get()->GetBlock(x, y, min) : nullptr;
		blockNeighbors[Direction::Back]		= z > min		? &m_Blocks[x][y][z-1] : m_ChunkNeighbors[Direction::Back].lock().get() ? m_ChunkNeighbors[Direction::Back].lock().get()->GetBlock(x, y, maxSize) : nullptr;
		blockNeighbors[Direction::Top]		= y < maxHeight ? &m_Blocks[x][y+1][z] : nullptr;
		blockNeighbors[Direction::Bottom]	= y > min		? &m_Blocks[x][y-1][z] : nullptr;

		return blockNeighbors;
	}

	bool Chunk::IsBlockVisible(int x, int y, int z)
	{
		auto& blockNeighbors = GetBlockNeighbors(x, y, z);

		for (Block* neighbor : blockNeighbors)
		{
			if (!neighbor || neighbor->BlockType == BlockType::Air)
			{
				return true;
			}
		}

		return false;
	}
}