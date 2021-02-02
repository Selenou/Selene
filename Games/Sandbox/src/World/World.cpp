#include "World.h"

namespace Sandbox
{
	void World::GenerateChunks()
	{
		int range = WorldConfig::DYNAMIC_WORLD_RADIUS;

		for (int x = -range; x <= range; x++)
		{
			for (int y = -range; y <= range; y++)
			{
				glm::vec2 chunkPosition = { x * WorldConfig::CHUNK_SIZE, y * WorldConfig::CHUNK_SIZE };

				if (glm::distance(glm::vec2({ x, y }), { 0, 0 }) < WorldConfig::CHUNK_DISTANCE_THRESHOLD)
				{
					m_ChunksMap.emplace(glm::vec2({ x,y }), std::make_shared<Chunk>(chunkPosition));
				}
			}
		}

		for (auto const& [chunkIndex, chunkPtr] : m_ChunksMap)
		{
			//SetChunkNeighbors(chunkIndex.x, chunkIndex.y);
			chunkPtr->GenerateMesh();
		}
	}
	
	void World::Render()
	{
		for (auto const& [chunkIndex, chunkPtr] : m_ChunksMap)
		{
			chunkPtr->Render();
		}
	}

	void World::Update(glm::vec3 playerPosition)
	{
		std::vector<glm::vec2> chunksDeletion;
		float chunkDistance;

		// Check which chunks need to be deleted
		for (auto& [chunkIndex, chunkPtr] : m_ChunksMap)
		{
			chunkDistance = glm::distance(chunkPtr->m_ChunkPosition, { playerPosition.x, playerPosition.z }) / WorldConfig::CHUNK_SIZE;
			
			if (chunkDistance >= WorldConfig::CHUNK_DISTANCE_THRESHOLD)
			{
				chunksDeletion.emplace_back(chunkIndex);
			}
		}

		// Delete old chunks
		for (auto& chunkIndex : chunksDeletion)
		{
			m_ChunksMap.erase(chunkIndex);
		}

		if (chunksDeletion.size() > 0)
		{
			// Construction loop
			int playerX = (int)round(playerPosition.x / WorldConfig::CHUNK_SIZE);
			int playerZ = (int)round(playerPosition.z / WorldConfig::CHUNK_SIZE);
			int range = WorldConfig::DYNAMIC_WORLD_RADIUS;

			for (int x = playerX - range; x <= playerX + range; x++)
			{
				for (int y = playerZ - range; y <= playerZ + range; y++)
				{
					glm::vec2 chunkCandidateIndex = { x,y };

					// If chunk candidate is not already created, check if it should be
					if (m_ChunksMap.find(chunkCandidateIndex) == m_ChunksMap.end())
					{
						glm::vec2 chunkCandidateWorldPosition = { x * WorldConfig::CHUNK_SIZE, y * WorldConfig::CHUNK_SIZE };
						chunkDistance = glm::distance(chunkCandidateWorldPosition, { playerPosition.x, playerPosition.z }) / WorldConfig::CHUNK_SIZE;

						if (chunkDistance < WorldConfig::CHUNK_DISTANCE_THRESHOLD)
						{
							std::shared_ptr<Chunk> newChunk = std::make_shared<Chunk>(chunkCandidateWorldPosition);
							m_ChunksMap.emplace(chunkCandidateIndex, newChunk);
							newChunk->GenerateMesh();
							//SLN_TRACE("Generate {0},{1}", x, y);
						}
					}
				}
			}
		}
	}

	void World::SetChunkNeighbors(int x, int y)
	{
		const int min = -WorldConfig::DYNAMIC_WORLD_RADIUS /2;
		const int max = WorldConfig::DYNAMIC_WORLD_RADIUS /2;

		std::array<std::shared_ptr<Chunk>, 4> neighbors;

		neighbors[Direction::Left]	= (x - 1 >= min) ? m_ChunksMap.at({x-1,y}) : nullptr;
		neighbors[Direction::Right] = (x + 1 <= max) ? m_ChunksMap.at({x+1,y}) : nullptr;
		neighbors[Direction::Front] = (y + 1 <= max) ? m_ChunksMap.at({x,y+1}) : nullptr;
		neighbors[Direction::Back]	= (y - 1 >= min) ? m_ChunksMap.at({x,y-1}) : nullptr;

		m_ChunksMap.at({x,y})->SetNeighbors(neighbors);
	}
}