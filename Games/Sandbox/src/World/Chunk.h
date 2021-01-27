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
		Chunk(int x, int y);
	public:
		void GenerateMesh();
		void Render();
		void SetNeighbors(std::array<std::shared_ptr<Chunk>, 4> neighbors);
	public:
		inline Block* GetBlock(int x, int y, int z) { return &m_Blocks[x][y][z]; }
	private:
		void FillChunk(BlockType type = BlockType::Air);
		std::array<Block*, 6> GetBlockNeighbors(int x, int y, int z);
		bool IsBlockVisible(int x, int y, int z);
	private:
		int m_ChunkOffsetX, m_ChunkOffsetY;
		std::shared_ptr<Selene::Mesh> m_Mesh;
		std::array<std::weak_ptr<Chunk>, 4> m_ChunkNeighbors;
		Block m_Blocks[WorldConfig::CHUNK_SIZE][WorldConfig::CHUNK_SIZE][WorldConfig::CHUNK_HEIGHT];
	};
}