#pragma once

#include "Selene.h"
#include "Chunk.h"
#include "FastNoiseLite.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp" // hashes for unordered_map

#include <deque>

namespace Sandbox
{
	class World
	{
	public:
		World() = default;
	public:
		void Init();
		void Render();
		void Update(glm::vec3 playerPosition);
	private:
		void SetChunkNeighbors(glm::vec2 chunkIndex, Direction direction = Direction::None);
		void RegenerateDirtyChunks(glm::vec2 chunkIndex);
		void GenerateChunkMesh();
	public:
		inline std::shared_ptr<Chunk> TryGetChunk(glm::vec2 chunkIndex) { return IsChunkLoaded(chunkIndex) ? m_ChunksMap.at(chunkIndex) : nullptr; }
		inline bool IsChunkLoaded(glm::vec2 chunkIndex) { return m_ChunksMap.find(chunkIndex) != m_ChunksMap.end(); }
	private:
		std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> m_ChunksMap;
		FastNoiseLite m_PerlinNoise;
		std::deque<glm::vec2> m_ChunkMeshBuilderQueue;
		std::deque<glm::vec2> m_ChunkMeshUpdateQueue;
	};
}