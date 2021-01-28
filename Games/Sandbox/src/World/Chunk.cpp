#include "Chunk.h"
#include <memory>

namespace Sandbox
{
	Chunk::Chunk(int x, int y) 
		: m_ChunkOffsetX(x * WorldConfig::CHUNK_SIZE), m_ChunkOffsetY(y * WorldConfig::CHUNK_SIZE)
	{
		FillChunk(BlockType::Dirt);
		m_Blocks[2][1][0] = { BlockType::Air };
	}

	void Chunk::GenerateMesh()
	{

		Greedy();
		return;
		std::vector<Selene::Vertex> vertices;
		std::vector<uint32_t> indices;

		int indicesCount = 0;

		for (int x = 0; x < WorldConfig::CHUNK_SIZE; x++)
		{
			for (int y = 0; y < WorldConfig::CHUNK_HEIGHT; y++)
			{
				for (int z = 0; z < WorldConfig::CHUNK_SIZE; z++)
				{
					Block block = m_Blocks[x][y][z];

					// If this block is visible 
					if (block.BlockType != BlockType::Air && IsBlockVisible(x, y, z))
					{
						for (int faceIndex = 0; faceIndex < 6; faceIndex++)
						{
							// Add visible faces only
							if (IsBlockFaceVisible(x, y, z, (Direction)faceIndex))
							{
								for (int i = 0; i < 30;)
								{
									Selene::Vertex vertex;
									vertex.Position = { BlockFaces::Faces[faceIndex][i++] + x, BlockFaces::Faces[faceIndex][i++] + y , BlockFaces::Faces[faceIndex][i++] + z };
									vertex.TexCoord = { BlockFaces::Faces[faceIndex][i++], BlockFaces::Faces[faceIndex][i++] };
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
		mat->Set(0, Selene::TextureCache::Load("assets/textures/box.png"));

		m_Mesh = std::make_shared<Selene::Mesh>("block", vertices, indices, mat);
		m_Mesh->SetPosition({ m_ChunkOffsetX, 0.0f, m_ChunkOffsetY }); // y is up
	}

	void Chunk::Render()
	{
		//Selene::RenderingEngine::SubmitMesh(m_Mesh);
		Selene::RenderingEngine::SubmitMesh(m_GreedyMesh);
	}

	void Chunk::SetNeighbors(std::array<std::shared_ptr<Chunk>, 4> neighbors)
	{
		for (int i = 0; i < 4; i++)
		{
			m_ChunkNeighbors[i] = neighbors[i];
		}
	}

	void Chunk::FillChunk(BlockType type)
	{
		for (int x = 0; x < WorldConfig::CHUNK_SIZE; x++)
		{
			for (int y = 0; y < WorldConfig::CHUNK_HEIGHT; y++)
			{
				for (int z = 0; z < WorldConfig::CHUNK_SIZE; z++)
				{
					m_Blocks[x][y][z] = { type };
				}
			}
		}
	}

	void Chunk::Greedy()
	{
		std::vector<Selene::Vertex> vertices;
		std::vector<uint32_t> indices;

		int indicesCount = 0;

		bool mask[WorldConfig::CHUNK_SIZE][WorldConfig::CHUNK_HEIGHT][WorldConfig::CHUNK_SIZE][6] = { false };

		for (int face = 0; face < 6; face++)
		{
			for (int x = 0; x < WorldConfig::CHUNK_SIZE; x++)
			{
				for (int y = 0; y < WorldConfig::CHUNK_HEIGHT; y++)
				{
					for (int z = 0; z < WorldConfig::CHUNK_SIZE; z++)
					{
						if (m_Blocks[x][y][z].BlockType != BlockType::Air && !mask[x][y][z][face] && IsBlockFaceVisible(x, y, z, (Direction)face))
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
												if (!mask[x][i][j][face] && m_Blocks[x][i][j].BlockType == m_Blocks[x][y][z].BlockType && IsBlockFaceVisible(x, i, j, (Direction)face))
												{
													width++;
												}
												else {
													break;
												}
											}
										}
										else
										{
											for (int j = 0; j < width; j++)
											{
												if (mask[x][i][z + j][face] || m_Blocks[x][i][z + j].BlockType != m_Blocks[x][y][z].BlockType || !IsBlockFaceVisible(x, i, z + j, (Direction)face))
												{
													run = false;
												}
											}
										}
										height++;
									}
									run = false;
								}

								for (int i = 0; i < height; i++)
								{
									for (int j = 0; j < width; j++)
									{
										mask[x][y + i][z + j][face] = true;
									}
								}

								if (face == Direction::Left)
								{
									for (int q = 0; q < 30;)
									{
										Selene::Vertex vertex;
										vertex.Position = { BlockFaces::Faces[Direction::Left][q++] + x, BlockFaces::Faces[Direction::Left][q++]* height + y + WorldConfig::CHUNK_HEIGHT/2 - 0.5, BlockFaces::Faces[Direction::Left][q++] * width + z + WorldConfig::CHUNK_SIZE / 2 - 0.5 };
										vertex.TexCoord = { BlockFaces::Faces[Direction::Left][q++]*height, BlockFaces::Faces[Direction::Left][q++]* width };
										vertices.emplace_back(vertex);
										indices.push_back(indicesCount++);
									}
								}
								else
								{
									for (int q = 0; q < 30;)
									{
										Selene::Vertex vertex;
										vertex.Position = { BlockFaces::Faces[Direction::Right][q++] + x, BlockFaces::Faces[Direction::Right][q++] * height + y + WorldConfig::CHUNK_HEIGHT / 2 - 0.5, BlockFaces::Faces[Direction::Right][q++] * width + z + WorldConfig::CHUNK_SIZE / 2 - 0.5 };
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
												if (!mask[j][i][z][face] && m_Blocks[j][i][z].BlockType == m_Blocks[x][y][z].BlockType && IsBlockFaceVisible(j, i, z, (Direction)face))
												{
													width++;
												}
												else {
													break;
												}
											}
										}
										else
										{
											for (int j = 0; j < width; j++)
											{
												if (mask[x+j][i][z][face] || m_Blocks[x+j][i][z].BlockType != m_Blocks[x][y][z].BlockType || !IsBlockFaceVisible(x+j, i, z, (Direction)face))
												{
													run = false;
												}
											}
										}
										height++;
									}
									run = false;
								}

								for (int i = 0; i < height; i++)
								{
									for (int j = 0; j < width; j++)
									{
										mask[x+j][y+i][z][face] = true;
									}
								}

								if (face == Direction::Front)
								{
									for (int q = 0; q < 30;)
									{
										Selene::Vertex vertex;
										vertex.Position = { BlockFaces::Faces[Direction::Front][q++] * width + x + WorldConfig::CHUNK_SIZE / 2 - 0.5, BlockFaces::Faces[Direction::Front][q++] * height + y + WorldConfig::CHUNK_HEIGHT / 2 - 0.5 , BlockFaces::Faces[Direction::Front][q++] + z };
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
										vertex.Position = { BlockFaces::Faces[Direction::Back][q++] * width + x + WorldConfig::CHUNK_SIZE / 2 - 0.5, BlockFaces::Faces[Direction::Back][q++] * height + y + WorldConfig::CHUNK_HEIGHT / 2 - 0.5, BlockFaces::Faces[Direction::Back][q++] + z };
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
												if (!mask[i][y][j][face] && m_Blocks[i][y][j].BlockType == m_Blocks[x][y][z].BlockType && IsBlockFaceVisible(i, y, j, (Direction)face))
												{
													width++;
												}
												else {
													break;
												}
											}
										}
										else
										{
											for (int j = 0; j < width; j++)
											{
												if (mask[i][y][z + j][face] || m_Blocks[i][y][z + j].BlockType != m_Blocks[x][y][z].BlockType || !IsBlockFaceVisible(i, y, z + j, (Direction)face))
												{
													run = false;
												}
											}
										}
										height++;
									}

									run = false;
								}

								for (int i = 0; i < height; i++)
								{
									for (int j = 0; j < width; j++)
									{
										mask[x + i][y][z + j][face] = true;
									}
								}

								if (face == Direction::Top)
								{
									for (int q = 0; q < 30;)
									{
										Selene::Vertex vertex;
										vertex.Position = { BlockFaces::Faces[Direction::Top][q++] * width + x + WorldConfig::CHUNK_SIZE / 2 - 0.5, BlockFaces::Faces[Direction::Top][q++] + y , BlockFaces::Faces[Direction::Top][q++] * height + z + WorldConfig::CHUNK_SIZE / 2 - 0.5 };
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
										vertex.Position = { BlockFaces::Faces[Direction::Bottom][q++] * width + x + WorldConfig::CHUNK_SIZE / 2 - 0.5, BlockFaces::Faces[Direction::Bottom][q++] + y, BlockFaces::Faces[Direction::Bottom][q++] * height + z + WorldConfig::CHUNK_SIZE / 2 - 0.5 };
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

		m_GreedyMesh = std::make_shared<Selene::Mesh>("block", vertices, indices, mat);
		m_GreedyMesh->SetPosition({ m_ChunkOffsetX, 0.0f, m_ChunkOffsetY }); // y is up
	}

	std::array<Block*, 6> Chunk::GetBlockNeighbors(int x, int y, int z)
	{
		const int min = 0;
		const int maxSize = WorldConfig::CHUNK_SIZE - 1;
		const int maxHeight = WorldConfig::CHUNK_HEIGHT - 1;

		std::array<Block*, 6> blockNeighbors;
		blockNeighbors[Direction::Left]		= x > min		? &m_Blocks[x-1][y][z] : m_ChunkNeighbors[Direction::Left].lock().get() ? m_ChunkNeighbors[Direction::Left].lock().get()->GetBlock(maxSize, y, z) : nullptr;
		blockNeighbors[Direction::Right]	= x < maxSize	? &m_Blocks[x+1][y][z] : m_ChunkNeighbors[Direction::Right].lock().get() ? m_ChunkNeighbors[Direction::Right].lock().get()->GetBlock(min, y, z) : nullptr;
		blockNeighbors[Direction::Front]	= z < maxSize	? &m_Blocks[x][y][z+1] : m_ChunkNeighbors[Direction::Front].lock().get() ? m_ChunkNeighbors[Direction::Front].lock().get()->GetBlock(x, y, min) : nullptr;
		blockNeighbors[Direction::Back]		= z > min		? &m_Blocks[x][y][z-1] : m_ChunkNeighbors[Direction::Back].lock().get() ? m_ChunkNeighbors[Direction::Back].lock().get()->GetBlock(x, y, maxSize) : nullptr;
		blockNeighbors[Direction::Top]		= y < maxHeight ? &m_Blocks[x][y+1][z] : nullptr;
		blockNeighbors[Direction::Bottom]	= y > min		? &m_Blocks[x][y-1][z] : nullptr;

		return blockNeighbors;
	}

	bool Chunk::IsBlockVisible(int x, int y, int z)
	{
		auto& blockNeighbors = GetBlockNeighbors(x, y, z);

		for (Block* neighbor : blockNeighbors)
		{
			if (!neighbor || neighbor->BlockType == BlockType::Air)
			{
				return true;
			}
		}

		return false;
	}

	bool Chunk::IsBlockFaceVisible(int x, int y, int z, Direction faceDirection)
	{
		auto& blockNeighbor = GetBlockNeighbors(x, y, z)[faceDirection];

		if (!blockNeighbor || blockNeighbor->BlockType == BlockType::Air)
		{
			return true;
		}

		return false;
	}
}