#include "World.h"
#include "FastNoiseLite.h"

namespace Sandbox
{
	void World::Init()
	{

		// TEST NOISE
		FastNoiseLite perlinNoise;
		perlinNoise.SetSeed(1337);
		perlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		const float frequency = 5.0f; // Higher frequency implies abrupt terrain
		const float amplitude = 20;
		const float minimumHeight = 4;


		int range = WorldConfig::DYNAMIC_WORLD_RADIUS;

		for (int x = -range; x <= range; x++)
		{
			for (int y = -range; y <= range; y++)
			{
				if (glm::distance(glm::vec2({ x, y }), { 0, 0 }) < WorldConfig::CHUNK_DISTANCE_THRESHOLD)
				{
					m_ChunksMap.emplace(glm::vec2({ x,y }), std::make_shared<Chunk>(glm::vec2({ x * WorldConfig::CHUNK_SIZE, y * WorldConfig::CHUNK_SIZE })));
					float perlinValue = (((perlinNoise.GetNoise(x * frequency, y * frequency) + 1.0f) / 2.0f) * amplitude) + minimumHeight - amplitude * 0.5f;
					SLN_TRACE("{0}", perlinValue);
				}
			}
		}

		for (auto const& [chunkIndex, chunkPtr] : m_ChunksMap)
		{
			SetChunkNeighbors(chunkIndex);
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
			RegenerateDirtyChunks(chunkIndex); // Regenerate adjacent chunk in order to reconstruct greedy mesh
		}

		if (chunksDeletion.size() > 0)
		{
			int playerX = (int)round(playerPosition.x / WorldConfig::CHUNK_SIZE);
			int playerZ = (int)round(playerPosition.z / WorldConfig::CHUNK_SIZE);
			int range = WorldConfig::DYNAMIC_WORLD_RADIUS;

			for (int x = playerX - range; x <= playerX + range; x++)
			{
				for (int y = playerZ - range; y <= playerZ + range; y++)
				{
					glm::vec2 chunkCandidateIndex = { x,y };

					// If chunk candidate is not already created, check if it should be
					if (!IsChunkLoaded(chunkCandidateIndex))
					{
						glm::vec2 chunkCandidateWorldPosition = { x * WorldConfig::CHUNK_SIZE, y * WorldConfig::CHUNK_SIZE };
						chunkDistance = glm::distance(chunkCandidateWorldPosition, { playerPosition.x, playerPosition.z }) / WorldConfig::CHUNK_SIZE;

						if (chunkDistance < WorldConfig::CHUNK_DISTANCE_THRESHOLD)
						{
							std::shared_ptr<Chunk> newChunk = std::make_shared<Chunk>(chunkCandidateWorldPosition);
							m_ChunksMap.emplace(chunkCandidateIndex, newChunk);
							SetChunkNeighbors(chunkCandidateIndex);
							newChunk->GenerateMesh();

							RegenerateDirtyChunks(chunkCandidateIndex); // Regenerate adjacent chunk in order to reconstruct greedy mesh
						}
					}
				}
			}
		}
	}

	void World::SetChunkNeighbors(glm::vec2 chunkIndex, Direction direction)
	{
		int x = (int)chunkIndex.x;
		int y = (int)chunkIndex.y;

		if(direction == Direction::None)
		{ 
			std::array<std::shared_ptr<Chunk>, 4> neighbors;

			neighbors[Direction::Left]	= TryGetChunk({ x - 1, y });
			neighbors[Direction::Right] = TryGetChunk({ x + 1, y });
			neighbors[Direction::Front] = TryGetChunk({ x, y + 1 });
			neighbors[Direction::Back]	= TryGetChunk({ x, y - 1 });

			m_ChunksMap.at(chunkIndex)->SetNeighbors(neighbors);
		}
		else
		{
			std::shared_ptr<Chunk> chunk = nullptr;

			switch (direction)
			{
				case Sandbox::Front:	chunk = TryGetChunk({ x, y + 1 }); break;
				case Sandbox::Back:		chunk = TryGetChunk({ x, y - 1 }); break;
				case Sandbox::Left:		chunk = TryGetChunk({ x - 1, y }); break;
				case Sandbox::Right:	chunk = TryGetChunk({ x + 1, y }); break;
			}

			m_ChunksMap.at(chunkIndex)->SetNeighbor(chunk, direction);
		}
	}

	void World::RegenerateDirtyChunks(glm::vec2 chunkIndex)
	{
		int x = (int)chunkIndex.x;
		int y = (int)chunkIndex.y;

		// Update all Neighbors
		if (IsChunkLoaded({ x - 1, y }))
		{
			SetChunkNeighbors({ x - 1, y }, Direction::Right);
		}
		if (IsChunkLoaded({ x + 1, y }))
		{
			SetChunkNeighbors({ x + 1, y }, Direction::Left);
		}
		if (IsChunkLoaded({ x, y + 1 }))
		{
			SetChunkNeighbors({ x, y + 1 }, Direction::Back);
		}
		if (IsChunkLoaded({ x, y - 1 }))
		{
			SetChunkNeighbors({ x, y - 1 }, Direction::Front);
		}

		// Regenerate all greedy meshes
		if (IsChunkLoaded({ x - 1, y }))
		{
			m_ChunksMap.at({ x - 1, y })->GenerateMesh();
		}
		if (IsChunkLoaded({ x + 1, y }))
		{
			m_ChunksMap.at({ x + 1, y })->GenerateMesh();
		}
		if (IsChunkLoaded({ x, y + 1 }))
		{
			m_ChunksMap.at({ x, y + 1 })->GenerateMesh();
		}
		if (IsChunkLoaded({ x, y - 1 }))
		{
			m_ChunksMap.at({ x, y - 1 })->GenerateMesh();
		}
	}
}