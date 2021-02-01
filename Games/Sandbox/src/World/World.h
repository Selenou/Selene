#pragma once

#include "Selene.h"
#include "Chunk.h"

namespace Sandbox
{
	class World
	{
	public:
		World() = default;
	public:
		void GenerateChunks();
		void Render();
		void Update(glm::vec3 playerPosition);
	private:
		void SetChunkNeighbors(int x, int y);
	private:
		std::array<std::array<std::shared_ptr<Chunk>, WorldConfig::WORLD_SIZE>, WorldConfig::WORLD_SIZE> m_Chunks;
		std::unordered_map<uint32_t, uint32_t> m_ChunksMap;
	};
}