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
			for (int y = 0; y < WorldConfig::CHUNK_SIZE; y++)
			{
				for (int z = 0; z < WorldConfig::CHUNK_HEIGHT; z++)
				{
					Block block = m_Blocks[x][y][z];

					if (block.BlockType != BlockType::Air)
					{
						if (IsBlockVisible(x, y, z))
						{
							for (int i = 0; i < Vertices.size(); i+=5)
							{
								Selene::Vertex vertex;
								vertex.Position = { Vertices[i] + x + m_ChunkOffsetX, Vertices[i + 1] - z , Vertices[i + 2] + y + m_ChunkOffsetY };
								vertex.TexCoord = { Vertices[i + 3], Vertices[i + 4] };
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

		auto& mat = Selene::Material::Create(Selene::RenderingEngine::GetShaderLibrary()->Get("unlit/unlitTexture"));
		mat->Set(0, Selene::TextureCache::Load("assets/meshes/cube/dirt.png"));

		m_Mesh = std::make_shared<Selene::Mesh>("block", vertices, indices, mat);
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
			for (int y = 0; y < WorldConfig::CHUNK_SIZE; y++)
			{
				for (int z = 0; z < WorldConfig::CHUNK_HEIGHT; z++)
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

		if (x == 15 && y == 1)
			int t = 2;

		std::array<Block*, 6> blockNeighbors;
		blockNeighbors[Direction::Left]		= x > min		? &m_Blocks[x-1][y][z] : m_ChunkNeighbors[Direction::Left].lock().get() ? m_ChunkNeighbors[Direction::Left].lock().get()->GetBlock(maxSize, y, z) : nullptr;



		//blockNeighbors[Direction::Right]	= x < maxSize	? &m_Blocks[x+1][y][z] : m_ChunkNeighbors[Direction::Right].lock().get() ? m_ChunkNeighbors[Direction::Right].lock().get()->GetBlock(min, y, z) : nullptr;


		//DEBUG
		if (x < maxSize)
		{
			blockNeighbors[Direction::Right] = &m_Blocks[x + 1][y][z];
		}
		else
		{
			if(m_ChunkNeighbors[Direction::Right].lock().get())
			{
				blockNeighbors[Direction::Right] = m_ChunkNeighbors[Direction::Right].lock().get()->GetBlock(min, y, z);
			}
			else
			{
				blockNeighbors[Direction::Right] = nullptr;
			}
		}




		blockNeighbors[Direction::Front]	= y < maxSize	? &m_Blocks[x][y+1][z] : m_ChunkNeighbors[Direction::Front].lock().get() ? m_ChunkNeighbors[Direction::Front].lock().get()->GetBlock(x, min, z) : nullptr;
		blockNeighbors[Direction::Back]		= y > min		? &m_Blocks[x][y-1][z] : m_ChunkNeighbors[Direction::Back].lock().get() ? m_ChunkNeighbors[Direction::Back].lock().get()->GetBlock(x, maxSize, z) : nullptr;
		blockNeighbors[Direction::Top]		= z < maxHeight ? &m_Blocks[x][y][z+1] : nullptr;
		blockNeighbors[Direction::Bottom]	= z > min		? &m_Blocks[x][y][z-1] : nullptr;

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