#include "Chunk.h"

namespace Sandbox
{
	Chunk::Chunk(int x, int y) 
		: m_ChunkOffsetX(x * WorldConfig::CHUNK_SIZE), m_ChunkOffsetY(y * WorldConfig::CHUNK_SIZE)
	{
		FillChunk();

		for (int x = 0; x < WorldConfig::CHUNK_SIZE; x++)
		{
			for (int y = 0; y < WorldConfig::CHUNK_HEIGHT; y++)
			{
				for (int z = 0; z < WorldConfig::CHUNK_SIZE; z++)
				{
					if (y > WorldConfig::CHUNK_HEIGHT - 2)
						m_Blocks[x][y][z] = { BlockType::Grass };
					else if (y > WorldConfig::CHUNK_HEIGHT - 4)
						m_Blocks[x][y][z] = { BlockType::Dirt };
					else
						m_Blocks[x][y][z] = { BlockType::Gravel };
				}
			}
		}
	}

	void Chunk::GenerateMesh()
	{
		auto t= Selene::Time::GetTime();
		GenerateGreedyMesh();
		SLN_WARN("Greedy meshing generaton : {0}s", Selene::Time::GetTime() - t);
	}

	void Chunk::Render()
	{
		Selene::RenderingEngine::SubmitMesh(m_Mesh);
	}

	void Chunk::SetNeighbors(std::array<std::shared_ptr<Chunk>, 4> neighbors)
	{
		std::copy(std::begin(neighbors), std::end(neighbors), std::begin(m_ChunkNeighbors)); // Neighbors uses Direction enum as index
	}

	void Chunk::FillChunk(BlockType type)
	{
		for (int x = 0; x < WorldConfig::CHUNK_SIZE; x++)
		{
			for (int y = 0; y < WorldConfig::CHUNK_HEIGHT; y++)
			{
				for (int z = 0; z < WorldConfig::CHUNK_SIZE; z++)
				{
					m_Blocks[x][y][z].BlockType = type;
				}
			}
		}
	}

	void Chunk::GenerateGreedyMesh()
	{
		std::vector<Selene::Vertex> vertices;
		std::vector<uint32_t> indices;
		int indicesCount = 0;
 
		bool runGreedyAlgorithm = false;
		auto greedyMask = new bool[WorldConfig::CHUNK_SIZE][WorldConfig::CHUNK_HEIGHT][WorldConfig::CHUNK_SIZE][6] { false };
		int greedyWidth = 0;
		int greedyHeight = 0;

		for (int face = 0; face < 6; face++)
		{
			for (int x = 0; x < WorldConfig::CHUNK_SIZE; x++)
			{
				for (int y = 0; y < WorldConfig::CHUNK_HEIGHT; y++)
				{
					for (int z = 0; z < WorldConfig::CHUNK_SIZE; z++)
					{
						if (m_Blocks[x][y][z].BlockType != BlockType::Air && !greedyMask[x][y][z][face] && IsBlockFaceVisible(x, y, z, (Direction)face))
						{
							greedyWidth = 0;
							greedyHeight = 0;
							runGreedyAlgorithm = true;

							if (face == Direction::Left || face == Direction::Right)
							{
								do
								{
									for (int i = y; i < WorldConfig::CHUNK_HEIGHT; i++)
									{
										if (i == y)
										{
											for (int j = z; j < WorldConfig::CHUNK_SIZE; j++)
											{
												if (!greedyMask[x][i][j][face] && m_Blocks[x][i][j].BlockType == m_Blocks[x][y][z].BlockType && IsBlockFaceVisible(x, i, j, (Direction)face))
													greedyWidth++;
												else
													break;
											}
										}
										else
										{
											for (int j = 0; j < greedyWidth; j++)
											{
												if (greedyMask[x][i][z + j][face] || m_Blocks[x][i][z + j].BlockType != m_Blocks[x][y][z].BlockType || !IsBlockFaceVisible(x, i, z + j, (Direction)face))
													runGreedyAlgorithm = false;
											}
										}

										if (runGreedyAlgorithm)
											greedyHeight++;
									}

									runGreedyAlgorithm = false;

								} while (runGreedyAlgorithm);

								for (int i = 0; i < greedyHeight; i++)
									for (int j = 0; j < greedyWidth; j++)
										greedyMask[x][y + i][z + j][face] = true;

								for (int vertexData = 0; vertexData < 30;)
								{
									Selene::Vertex vertex;
									vertex.Position = { BlockFaces::Faces[face][vertexData++] + x, BlockFaces::Faces[face][vertexData++] * greedyHeight + (greedyHeight - 1) / 2.0f + y, BlockFaces::Faces[face][vertexData++] * greedyWidth + (greedyWidth - 1) / 2.0f + z };
									vertex.TexCoord = { BlockFaces::Faces[face][vertexData++] * greedyHeight , BlockFaces::Faces[face][vertexData++] * greedyWidth };
									vertex.CustomFlags = static_cast<uint32_t>(m_Blocks[x][y][z].BlockType);
									vertices.emplace_back(vertex);
									indices.push_back(indicesCount++);
								}
							}
							else if (face == Direction::Front || face == Direction::Back)
							{
								do
								{
									for (int i = y; i < WorldConfig::CHUNK_HEIGHT; i++)
									{
										if (i == y)
										{
											for (int j = x; j < WorldConfig::CHUNK_SIZE; j++)
											{
												if (!greedyMask[j][i][z][face] && m_Blocks[j][i][z].BlockType == m_Blocks[x][y][z].BlockType && IsBlockFaceVisible(j, i, z, (Direction)face))
													greedyWidth++;
												else
													break;
											}
										}
										else
										{
											for (int j = 0; j < greedyWidth; j++)
											{
												if (greedyMask[x + j][i][z][face] || m_Blocks[x + j][i][z].BlockType != m_Blocks[x][y][z].BlockType || !IsBlockFaceVisible(x + j, i, z, (Direction)face))
													runGreedyAlgorithm = false;
											}
										}
										if (runGreedyAlgorithm)
											greedyHeight++;
									}

									runGreedyAlgorithm = false;

								} while (runGreedyAlgorithm);

								for (int i = 0; i < greedyHeight; i++)
									for (int j = 0; j < greedyWidth; j++)
										greedyMask[x + j][y + i][z][face] = true;

								for (int vertexData = 0; vertexData < 30;)
								{
									Selene::Vertex vertex;
									vertex.Position = { BlockFaces::Faces[face][vertexData++] * greedyWidth + (greedyWidth - 1) / 2.0f + x, BlockFaces::Faces[face][vertexData++] * greedyHeight + (greedyHeight - 1) / 2.0f + y, BlockFaces::Faces[face][vertexData++] + z };
									vertex.TexCoord = { BlockFaces::Faces[face][vertexData++] * greedyWidth , BlockFaces::Faces[face][vertexData++] * greedyHeight };
									vertex.CustomFlags = static_cast<uint32_t>(m_Blocks[x][y][z].BlockType);
									vertices.emplace_back(vertex);
									indices.push_back(indicesCount++);
								}
							}
							else
							{
								do
								{
									for (int i = x; i < WorldConfig::CHUNK_SIZE; i++)
									{
										if (i == x)
										{
											for (int j = z; j < WorldConfig::CHUNK_SIZE; j++)
											{
												if (!greedyMask[i][y][j][face] && m_Blocks[i][y][j].BlockType == m_Blocks[x][y][z].BlockType && IsBlockFaceVisible(i, y, j, (Direction)face))
													greedyWidth++;
												else
													break;
											}
										}
										else
										{
											for (int j = 0; j < greedyWidth; j++)
											{
												if (greedyMask[i][y][z + j][face] || m_Blocks[i][y][z + j].BlockType != m_Blocks[x][y][z].BlockType || !IsBlockFaceVisible(i, y, z + j, (Direction)face))
													runGreedyAlgorithm = false;
											}
										}
										if (runGreedyAlgorithm)
											greedyHeight++;
									}

									runGreedyAlgorithm = false;

								} while (runGreedyAlgorithm);



								for (int i = 0; i < greedyHeight; i++)
									for (int j = 0; j < greedyWidth; j++)
										greedyMask[x + i][y][z + j][face] = true;
									
								for (int vertexData = 0; vertexData < 30;)
								{
									Selene::Vertex vertex;
									vertex.Position = { BlockFaces::Faces[face][vertexData++] * greedyHeight + (greedyHeight - 1) / 2.0f + x, BlockFaces::Faces[face][vertexData++] + y , BlockFaces::Faces[face][vertexData++] * greedyWidth + (greedyWidth - 1) / 2.0f + z };
									vertex.TexCoord = { BlockFaces::Faces[face][vertexData++] * greedyHeight, BlockFaces::Faces[face][vertexData++] * greedyWidth };
									vertex.CustomFlags = static_cast<uint32_t>(m_Blocks[x][y][z].BlockType);
									vertices.emplace_back(vertex);
									indices.push_back(indicesCount++);
								}
							}
						}
					}
				}
			}
		}

		auto& mat = Selene::Material::Create(Selene::RenderingEngine::GetShaderLibrary()->Get("chunk"));
		mat->Set(0, Selene::TextureCache::LoadTextureArray("assets/textures/blockTextureAtlas.png", 8, 8));

		m_Mesh = std::make_shared<Selene::Mesh>("chunk", vertices, indices, mat);
		m_Mesh->SetPosition({ m_ChunkOffsetX, 0.0f, m_ChunkOffsetY }); // y is up

		delete[] greedyMask;
	}

	Block* Chunk::GetNeighborBlock(int x, int y, int z, Direction direction)
	{
		const int min = 0;
		const int maxSize = WorldConfig::CHUNK_SIZE - 1;
		const int maxHeight = WorldConfig::CHUNK_HEIGHT - 1;

		switch (direction)
		{
			case Direction::Front:	return z < maxSize		? &m_Blocks[x][y][z + 1] : m_ChunkNeighbors[Direction::Front].get()	? m_ChunkNeighbors[Direction::Front].get()->GetBlock(x, y, min)		: nullptr;
			case Direction::Back:	return z > min			? &m_Blocks[x][y][z - 1] : m_ChunkNeighbors[Direction::Back].get()	? m_ChunkNeighbors[Direction::Back].get()->GetBlock(x, y, maxSize)	: nullptr;
			case Direction::Left:	return x > min			? &m_Blocks[x - 1][y][z] : m_ChunkNeighbors[Direction::Left].get()	? m_ChunkNeighbors[Direction::Left].get()->GetBlock(maxSize, y, z)	: nullptr;
			case Direction::Right:	return x < maxSize		? &m_Blocks[x + 1][y][z] : m_ChunkNeighbors[Direction::Right].get()	? m_ChunkNeighbors[Direction::Right].get()->GetBlock(min, y, z)		: nullptr;
			case Direction::Top:	return y < maxHeight	? &m_Blocks[x][y + 1][z] : nullptr;
			case Direction::Bottom: return y > min			? &m_Blocks[x][y - 1][z] : nullptr;
			default:				return nullptr;
		}
	}

	bool Chunk::IsBlockFaceVisible(int x, int y, int z, Direction faceDirection)
	{
		auto blockNeighbor = GetNeighborBlock(x, y, z, faceDirection);

		if (!blockNeighbor || blockNeighbor->BlockType == BlockType::Air)
		{
			return true;
		}

		return false;
	}
}