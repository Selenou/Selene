#include "Chunk.h"
#include <memory>
#include <algorithm>
#include <array>

namespace Sandbox
{
	Chunk::Chunk(int x, int y) 
		: m_ChunkOffsetX(x * WorldConfig::CHUNK_SIZE), m_ChunkOffsetY(y * WorldConfig::CHUNK_SIZE)
	{
		FillChunk(BlockType::Dirt);
		m_Blocks[1][0][0] = { BlockType::Air };
		m_Blocks[1][1][0] = { BlockType::Air };
	}

	void Chunk::GenerateMesh()
	{
		auto t= Selene::Time::GetTime();
		Greedy();
		SLN_WARN("Greedy meshing generaton : {0}s", Selene::Time::GetTime() - t);
	}

	void Chunk::Render()
	{
		Selene::RenderingEngine::SubmitMesh(m_Mesh);
	}

	void Chunk::SetNeighbors(std::array<std::shared_ptr<Chunk>, 4> neighbors)
	{
		std::copy(std::begin(neighbors), std::end(neighbors), std::begin(m_ChunkNeighbors));
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

	void Chunk::Greedy()
	{
		std::vector<Selene::Vertex> vertices;
		std::vector<uint32_t> indices;
		int indicesCount = 0;
 
		auto greedyMask = new bool[WorldConfig::CHUNK_SIZE][WorldConfig::CHUNK_HEIGHT][WorldConfig::CHUNK_SIZE][6] { false };

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
								if (face == Direction::Left || face == Direction::Right)
								{
									int width = 0;
									int height = 0;
									bool run = true;

									while (run)
									{
										for (int i = y; i < WorldConfig::CHUNK_HEIGHT; i++)
										{
											if (i == y)
											{
												for (int j = z; j < WorldConfig::CHUNK_SIZE; j++)
												{
													if (!greedyMask[x][i][j][face] && m_Blocks[x][i][j].BlockType == m_Blocks[x][y][z].BlockType && IsBlockFaceVisible(x, i, j, (Direction)face))
													{
														width++;
													}
													else
													{
														break;
													}
												}
											}
											else
											{
												for (int j = 0; j < width; j++)
												{
													if (greedyMask[x][i][z + j][face] || m_Blocks[x][i][z + j].BlockType != m_Blocks[x][y][z].BlockType || !IsBlockFaceVisible(x, i, z + j, (Direction)face))
													{
														run = false;
													}
												}
											}
											if (run)
												height++;
										}
										run = false;
									}


									for (int i = 0; i < height; i++)
									{
										for (int j = 0; j < width; j++)
										{
											greedyMask[x][y + i][z + j][face] = true;
										}
									}

									if (face == Direction::Left)
									{
										for (int q = 0; q < 30;)
										{
											Selene::Vertex vertex;
											vertex.Position = { BlockFaces::Faces[Direction::Left][q++] + x, BlockFaces::Faces[Direction::Left][q++] * height + y + height / 2.0f - 0.5, BlockFaces::Faces[Direction::Left][q++] * width + z + width / 2.0f - 0.5 };
											vertex.TexCoord = { BlockFaces::Faces[Direction::Left][q++] * height, BlockFaces::Faces[Direction::Left][q++] * width };
											vertices.emplace_back(vertex);
											indices.push_back(indicesCount++);
										}
									}
									else
									{
										for (int q = 0; q < 30;)
										{
											Selene::Vertex vertex;
											vertex.Position = { BlockFaces::Faces[Direction::Right][q++] + x, BlockFaces::Faces[Direction::Right][q++] * height + y + height / 2.0f - 0.5, BlockFaces::Faces[Direction::Right][q++] * width + z + width / 2.0f - 0.5 };
											vertex.TexCoord = { BlockFaces::Faces[Direction::Right][q++] * height, BlockFaces::Faces[Direction::Right][q++] * width };
											vertices.emplace_back(vertex);
											indices.push_back(indicesCount++);
										}
									}
								}
								else if (face == Direction::Front || face == Direction::Back)
								{
									int width = 0;
									int height = 0;
									bool run = true;

									while (run)
									{
										for (int i = y; i < WorldConfig::CHUNK_HEIGHT; i++)
										{
											if (i == y)
											{
												for (int j = x; j < WorldConfig::CHUNK_SIZE; j++)
												{
													if (!greedyMask[j][i][z][face] && m_Blocks[j][i][z].BlockType == m_Blocks[x][y][z].BlockType && IsBlockFaceVisible(j, i, z, (Direction)face))
													{
														width++;
													}
													else
													{
														break;
													}
												}
											}
											else
											{
												for (int j = 0; j < width; j++)
												{
													if (greedyMask[x + j][i][z][face] || m_Blocks[x + j][i][z].BlockType != m_Blocks[x][y][z].BlockType || !IsBlockFaceVisible(x + j, i, z, (Direction)face))
													{
														run = false;
													}
												}
											}
											if (run)
												height++;
										}
										run = false;
									}


									for (int i = 0; i < height; i++)
									{
										for (int j = 0; j < width; j++)
										{
											greedyMask[x + j][y + i][z][face] = true;
										}
									}

									if (face == Direction::Front)
									{
										for (int q = 0; q < 30;)
										{
											Selene::Vertex vertex;
											vertex.Position = { BlockFaces::Faces[Direction::Front][q++] * width + x + width / 2.0f - 0.5, BlockFaces::Faces[Direction::Front][q++] * height + y + height / 2.0f - 0.5 , BlockFaces::Faces[Direction::Front][q++] + z };
											vertex.TexCoord = { BlockFaces::Faces[Direction::Front][q++] * width , BlockFaces::Faces[Direction::Front][q++] * height };
											vertices.emplace_back(vertex);
											indices.push_back(indicesCount++);
										}
									}
									else
									{
										for (int q = 0; q < 30;)
										{
											Selene::Vertex vertex;
											vertex.Position = { BlockFaces::Faces[Direction::Back][q++] * width + x + width / 2.0f - 0.5, BlockFaces::Faces[Direction::Back][q++] * height + y + height / 2.0f - 0.5, BlockFaces::Faces[Direction::Back][q++] + z };
											vertex.TexCoord = { BlockFaces::Faces[Direction::Back][q++] * width, BlockFaces::Faces[Direction::Back][q++] * height };
											vertices.emplace_back(vertex);
											indices.push_back(indicesCount++);
										}
									}
								}
								else
								{
									int width = 0;
									int height = 0;
									bool run = true;

									while (run)
									{
										for (int i = x; i < WorldConfig::CHUNK_SIZE; i++)
										{
											if (i == x)
											{
												for (int j = z; j < WorldConfig::CHUNK_SIZE; j++)
												{
													if (!greedyMask[i][y][j][face] && m_Blocks[i][y][j].BlockType == m_Blocks[x][y][z].BlockType && IsBlockFaceVisible(i, y, j, (Direction)face))
													{
														width++;
													}
													else
													{
														break;
													}
												}
											}
											else
											{
												for (int j = 0; j < width; j++)
												{
													if (greedyMask[i][y][z + j][face] || m_Blocks[i][y][z + j].BlockType != m_Blocks[x][y][z].BlockType || !IsBlockFaceVisible(i, y, z + j, (Direction)face))
													{
														run = false;
													}
												}
											}
											if (run)
												height++;
										}

										run = false;
									}


									for (int i = 0; i < height; i++)
									{
										for (int j = 0; j < width; j++)
										{
											greedyMask[x + i][y][z + j][face] = true;
										}
									}

									if (face == Direction::Top)
									{
										for (int q = 0; q < 30;)
										{
											Selene::Vertex vertex;
											vertex.Position = { BlockFaces::Faces[Direction::Top][q++] * height + x + height / 2.0f - 0.5, BlockFaces::Faces[Direction::Top][q++] + y , BlockFaces::Faces[Direction::Top][q++] * width + z + width / 2.0f - 0.5 };
											vertex.TexCoord = { BlockFaces::Faces[Direction::Top][q++] * height, BlockFaces::Faces[Direction::Top][q++] * width };
											vertices.emplace_back(vertex);
											indices.push_back(indicesCount++);
										}
									}
									else
									{
										for (int q = 0; q < 30;)
										{
											Selene::Vertex vertex;
											vertex.Position = { BlockFaces::Faces[Direction::Bottom][q++] * height + x + height / 2.0f - 0.5, BlockFaces::Faces[Direction::Bottom][q++] + y, BlockFaces::Faces[Direction::Bottom][q++] * width + z + width / 2.0f - 0.5 };
											vertex.TexCoord = { BlockFaces::Faces[Direction::Bottom][q++] * height, BlockFaces::Faces[Direction::Bottom][q++] * width };
											vertices.emplace_back(vertex);
											indices.push_back(indicesCount++);
										}
									}

								}
							}
						
					}
				}
			}
		}

		auto& mat = Selene::Material::Create(Selene::RenderingEngine::GetShaderLibrary()->Get("chunk"));
		mat->Set(0, Selene::TextureCache::Load("assets/textures/box.png"));

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
			case Direction::Front:	return z < maxSize		? &m_Blocks[x][y][z + 1] : m_ChunkNeighbors[Direction::Front].lock().get()	? m_ChunkNeighbors[Direction::Front].lock().get()->GetBlock(x, y, min)		: nullptr;
			case Direction::Back:	return z > min			? &m_Blocks[x][y][z - 1] : m_ChunkNeighbors[Direction::Back].lock().get()	? m_ChunkNeighbors[Direction::Back].lock().get()->GetBlock(x, y, maxSize)	: nullptr;
			case Direction::Left:	return x > min			? &m_Blocks[x - 1][y][z] : m_ChunkNeighbors[Direction::Left].lock().get()	? m_ChunkNeighbors[Direction::Left].lock().get()->GetBlock(maxSize, y, z)	: nullptr;
			case Direction::Right:	return x < maxSize		? &m_Blocks[x + 1][y][z] : m_ChunkNeighbors[Direction::Right].lock().get()	? m_ChunkNeighbors[Direction::Right].lock().get()->GetBlock(min, y, z)		: nullptr;
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