#include "World.h"

namespace Sandbox
{
	void World::GenerateChunks()
	{
		for (int x = 0; x < WorldConfig::WORLD_SIZE; x++)
		{
			for (int y = 0; y < WorldConfig::WORLD_SIZE; y++)
			{
				m_Chunks[x][y] = std::make_shared<Chunk>(x, y);
			}
		}

		for (int x = 0; x < WorldConfig::WORLD_SIZE; x++)
		{
			for (int y = 0; y < WorldConfig::WORLD_SIZE; y++)
			{
				SetChunkNeighbors(x, y);
				m_Chunks[x][y]->GenerateMesh();
			}
		}
	}

	void World::Render()
	{
		for (auto& chunkRows : m_Chunks)
		{
			for (auto& chunk : chunkRows)
			{
				chunk.get()->Render();
			}
		}
	}

	void World::SetChunkNeighbors(int x, int y)
	{
		const int min = 0;
		const int maxSize = WorldConfig::WORLD_SIZE - 1;

		std::array<std::shared_ptr<Chunk>, 4> neighbors;

		neighbors[Direction::Left]	= (x - 1 >= min)		? m_Chunks[x-1][y] : nullptr;
		neighbors[Direction::Right] = (x + 1 <= maxSize)	? m_Chunks[x+1][y] : nullptr;
		neighbors[Direction::Front] = (y + 1 <= maxSize)	? m_Chunks[x][y+1] : nullptr;
		neighbors[Direction::Back]	= (y - 1 >= min)		? m_Chunks[x][y-1] : nullptr;

		m_Chunks[x][y]->SetNeighbors(neighbors);
	}
}