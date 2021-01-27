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
	private:
		void SetChunksNeighbors();
	private:
		std::array<std::array<std::shared_ptr<Chunk>, WorldConfig::WORLD_SIZE>, WorldConfig::WORLD_SIZE> m_Chunks;
	};
}