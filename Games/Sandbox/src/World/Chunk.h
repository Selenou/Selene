#pragma once

#include "Selene.h"
#include "Block.h"
#include "WorldConfig.h"

namespace Sandbox
{
	enum Direction
	{
		Front,
		Back,
		Left,
		Right,
		Top,
		Bottom
	};

	class Chunk
	{
	public:
		Chunk();
	public:
		void GenerateMesh();
		void Render();
	private:
		void FillChunk(BlockType type = BlockType::Air);
		std::array<Block*, 6> GetBlockNeighbors(int x, int y, int z);
		bool IsBlockVisible(int x, int y, int z);
	private:
		std::shared_ptr<Selene::Mesh> m_Mesh;
		Block m_Blocks[WorldConfig::CHUNK_SIZE][WorldConfig::CHUNK_SIZE][WorldConfig::CHUNK_HEIGHT];
	};
}