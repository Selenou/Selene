#pragma once

#include "Selene.h"
#include "BlockUtils.h"
#include "WorldConfig.h"

namespace Sandbox
{
	class Chunk
	{
	friend class World;

	public:
		Chunk(glm::vec2& chunkPosition);
	public:
		void GenerateMesh();
		void Render();
		void SetNeighbors(std::array<std::shared_ptr<Chunk>, 4> neighbors);
	public:
		inline void SetNeighbor(std::shared_ptr<Chunk> neighbor, Direction direction) { m_ChunkNeighbors[direction] = neighbor; }
		inline Block* GetBlock(int x, int y, int z) { return &m_Blocks[x][y][z]; }
	private:
		void FillChunk(BlockType type = BlockType::Air);
		void GenerateGreedyMesh();
		Block* GetNeighborBlock(int x, int y, int z, Direction direction);
		bool IsBlockFaceVisible(int x, int y, int z, Direction faceDirection);
	private:
		glm::vec2 m_ChunkPosition;
		std::shared_ptr<Selene::Mesh> m_Mesh;
		std::array<std::shared_ptr<Chunk>, 4> m_ChunkNeighbors; // weak_ptr increases generation time by 7% for greedy meshing due to the lock() mechanism which cost a lot
		Block m_Blocks[WorldConfig::CHUNK_SIZE][WorldConfig::CHUNK_HEIGHT][WorldConfig::CHUNK_SIZE];
	};
}