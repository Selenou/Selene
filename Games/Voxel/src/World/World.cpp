#include "World.h"

namespace Voxel
{
	void World::Init()
	{
		auto t = Selene::Time::GetTime();
		{
			m_PerlinNoise.SetSeed(1337);
			m_PerlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
			//m_PerlinNoise.SetFrequency(0.01f);

			int range = WorldConfig::DYNAMIC_WORLD_RADIUS;

			for (int x = -range; x <= range; x++)
			{
				for (int y = -range; y <= range; y++)
				{
					if (glm::distance(glm::vec2({ x, y }), { 0, 0 }) < WorldConfig::CHUNK_DISTANCE_THRESHOLD)
					{
						auto& chunkPtr = std::make_shared<Chunk>(glm::vec2({ x * WorldConfig::CHUNK_SIZE, y * WorldConfig::CHUNK_SIZE }));
						chunkPtr->Populate(m_PerlinNoise);
						m_ChunksMap.emplace(glm::vec2({ x,y }), chunkPtr);
					}
				}
			}

			for (auto const& [chunkIndex, chunkPtr] : m_ChunksMap)
			{
				SetChunkNeighbors(chunkIndex);
				chunkPtr->GenerateMesh();
			}
		}
		SLN_WARN("World generation : %fs", Selene::Time::GetTime() - t);
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
							newChunk->Populate(m_PerlinNoise);
							m_ChunksMap.emplace(chunkCandidateIndex, newChunk);
							SetChunkNeighbors(chunkCandidateIndex);
							m_ChunkMeshBuilderQueue.push_back(chunkCandidateIndex);
							RegenerateDirtyChunks(chunkCandidateIndex); // Regenerate adjacent chunk in order to reconstruct greedy mesh
						}
					}
				}
			}
		}

		GenerateChunkMesh(); // one call per frame, using a queue system to keep the game smooth on a single thread since greedy mesh is expensive
	}

	void World::GenerateChunkMesh()
	{
		if (!m_ChunkMeshBuilderQueue.empty())
		{
			auto& chunkIndex = m_ChunkMeshBuilderQueue.front();
			m_ChunkMeshBuilderQueue.pop_front();

			if (TryGetChunk(chunkIndex) != nullptr)
			{
				m_ChunksMap.at(chunkIndex)->GenerateMesh();
			}
			else
			{
				GenerateChunkMesh();
			}
		}
		else if (!m_ChunkMeshUpdateQueue.empty())
		{
			auto& chunkIndex = m_ChunkMeshUpdateQueue.front();
			m_ChunkMeshUpdateQueue.pop_front();

			if (TryGetChunk(chunkIndex) != nullptr)
			{
				m_ChunksMap.at(chunkIndex)->GenerateMesh();
			}
			else
			{
				GenerateChunkMesh();
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
				case Direction::Front:		chunk = TryGetChunk({ x, y + 1 });		break;
				case Direction::Back:		chunk = TryGetChunk({ x, y - 1 });		break;
				case Direction::Left:		chunk = TryGetChunk({ x - 1, y });		break;
				case Direction::Right:		chunk = TryGetChunk({ x + 1, y });		break;
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
			m_ChunkMeshUpdateQueue.push_back({ x - 1, y });
		}
		if (IsChunkLoaded({ x + 1, y }))
		{
			m_ChunkMeshUpdateQueue.push_back({ x + 1, y });
		}
		if (IsChunkLoaded({ x, y + 1 }))
		{
			m_ChunkMeshUpdateQueue.push_back({ x, y + 1 });
		}
		if (IsChunkLoaded({ x, y - 1 }))
		{
			m_ChunkMeshUpdateQueue.push_back({ x, y - 1 });
		}
	}
}