#pragma once

#include "Selene.h"
#include "Chunk.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp" // hashes for unordered_map

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
		std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> m_ChunksMap;
	};
}