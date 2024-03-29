#include "Map.h"

void Map::LoadStatic(tson::Map* map, tson::Vector2i worldPosition)
{
 	if (map->getStatus() == tson::ParseStatus::OK)
 	{
 		tson::Layer* tileLayer = map->getLayer("Static");

		if (tileLayer->getType() == tson::LayerType::TileLayer)
		{
			// Material
			{
				std::string tilesetName = map->getTileset("debugTileset")->getImage().u8string();
				m_Material = Selene::Material::Create(Selene::RenderingEngine::GetShaderLibrary()->Get("unlit/unlitTexture"));
				m_TilesetTexture = Selene::TextureCache::LoadTexture2D("assets/textures/" + tilesetName);
				m_Material->Set(0, m_TilesetTexture);
			}

			std::vector<float> vertices;
			std::vector<uint32_t> indices;
			int indicesOffset = 0;

			for (auto& [tilePos, tileObject] : tileLayer->getTileObjects())
			{
				tson::Rect drawingRect = tileObject.getDrawingRect();
				tson::Vector2f position = tileObject.getPosition();

				int tileWidth = drawingRect.width;
				int tileHeight = drawingRect.height;

 				// AABB, could do a kind of greedy meshing algorithm here to improve performance
				Selene::Actor tile = Selene::Game::GetInstance().GetActiveScene()->CreateActor("Tile");
				auto&& tileTransform = tile.GetComponent<Selene::TransformComponent>();
				tileTransform.Position = { worldPosition.x + position.x + tileWidth * 0.5f, -worldPosition.y - position.y - tileHeight * 0.5f, 0.0f };
				auto&& aabb = tile.AddComponent<Selene::AABBColliderComponent>();
				aabb.Size = { tileWidth, tileHeight };

				// Texture coords
				std::array<glm::vec2, 4> textureCoords;
				{
					glm::vec2 min = { drawingRect.x / (float)m_TilesetTexture->GetWidth(), 1.0f - (drawingRect.y / (float)m_TilesetTexture->GetHeight()) };
					glm::vec2 max = { (drawingRect.x + tileWidth) / (float)m_TilesetTexture->GetWidth(), 1.0f - ((drawingRect.y + tileHeight) / (float)m_TilesetTexture->GetHeight()) };

					textureCoords[0] = { min.x, max.y };
					textureCoords[1] = { max.x, max.y };
					textureCoords[2] = { max.x, min.y };
					textureCoords[3] = { min.x, min.y };
				}

				// Vertices
				{
					vertices.emplace_back(worldPosition.x + position.x);
					vertices.emplace_back(-worldPosition.y - position.y - tileHeight);
					vertices.emplace_back(-1.0f);
					vertices.emplace_back(textureCoords[0][0]);
					vertices.emplace_back(textureCoords[0][1]);

					vertices.emplace_back(worldPosition.x + position.x + tileWidth);
					vertices.emplace_back(-worldPosition.y - position.y - tileHeight);
					vertices.emplace_back(-1.0f);
					vertices.emplace_back(textureCoords[1][0]);
					vertices.emplace_back(textureCoords[1][1]);

					vertices.emplace_back(worldPosition.x + position.x + tileWidth);
					vertices.emplace_back(-worldPosition.y - position.y);
					vertices.emplace_back(-1.0f);
					vertices.emplace_back(textureCoords[2][0]);
					vertices.emplace_back(textureCoords[2][1]);

					vertices.emplace_back(worldPosition.x + position.x);
					vertices.emplace_back(-worldPosition.y - position.y);
					vertices.emplace_back(-1.0f);
					vertices.emplace_back(textureCoords[3][0]);
					vertices.emplace_back(textureCoords[3][1]);
				}

				// Indices
				{
					indices.emplace_back(indicesOffset + 0);
					indices.emplace_back(indicesOffset + 1);
					indices.emplace_back(indicesOffset + 2);
					indices.emplace_back(indicesOffset + 2);
					indices.emplace_back(indicesOffset + 3);
					indices.emplace_back(indicesOffset + 0);
				}

				indicesOffset += 4;
			}

			m_Vbo = Selene::VertexBuffer::Create(vertices.data(), (uint32_t)(vertices.size() * sizeof(float)));
			m_Ebo = Selene::IndexBuffer::Create(indices.data(), (uint32_t)(indices.size() * sizeof(uint32_t)));

			Selene::VertexBufferLayout layout = Selene::VertexBufferLayout({
					{ "a_Position", Selene::DataType::Float3 },
					{ "a_TexCoord", Selene::DataType::Float2 }
				});

			m_Vbo->SetLayout(layout);

			SetupPipeline();
		}
	}
}

void Map::SetupPipeline()
{
	m_Pipeline = Selene::Pipeline::Create();
	m_Pipeline->BindVertexBuffer(m_Vbo);
	m_Pipeline->BindIndexBuffer(m_Ebo);
}
