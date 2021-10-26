#pragma once

#include "Selene.h"
#include <string>

#pragma warning(disable : 4267 4018 4244)
#include <tileson.hpp>
#pragma warning(default : 4267 4018 4244)

class GameLayer;

class Map
{
public:
	Map() = default;
public:
	void LoadStatic(tson::Map* map, tson::Vector2i worldPosition);
private:
	void SetupPipeline();
private: 
	std::shared_ptr<Selene::VertexBuffer> m_Vbo;
	std::shared_ptr<Selene::IndexBuffer> m_Ebo;
	std::shared_ptr<Selene::Pipeline> m_Pipeline;
	std::shared_ptr<Selene::Material> m_Material;
	std::shared_ptr<Selene::Texture> m_TilesetTexture;

	friend class GameLayer;
};