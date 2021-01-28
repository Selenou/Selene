#pragma once

#include "Selene.h"
#include "Block.h"
#include "WorldConfig.h"

namespace Sandbox
{
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
		void Greedy();
		std::array<Block*, 6> GetBlockNeighbors(int x, int y, int z);
		bool IsBlockVisible(int x, int y, int z);
		bool IsBlockFaceVisible(int x, int y, int z, Direction faceDirection);
	private:
		int m_ChunkOffsetX, m_ChunkOffsetY;
		std::shared_ptr<Selene::Mesh> m_Mesh;
		std::shared_ptr<Selene::Mesh> m_GreedyMesh;
		std::array<std::weak_ptr<Chunk>, 4> m_ChunkNeighbors;
		Block m_Blocks[WorldConfig::CHUNK_SIZE][WorldConfig::CHUNK_HEIGHT][WorldConfig::CHUNK_SIZE];
	};
}