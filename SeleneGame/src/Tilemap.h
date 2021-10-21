#pragma once

#include "Selene.h"
#include <string>

class GameLayer;

class Tilemap
{
public:
	Tilemap() = default;
public:
	void ParseMap(const std::string& path);
private: 
	std::shared_ptr<Selene::VertexBuffer> m_Vbo;
	std::shared_ptr<Selene::IndexBuffer> m_Ebo;
	std::shared_ptr<Selene::Pipeline> m_Pipeline;
	std::shared_ptr<Selene::Material> m_Material;
	std::shared_ptr<Selene::Texture> m_TilesetTexture;

	friend class GameLayer;
};