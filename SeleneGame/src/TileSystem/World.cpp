#include "World.h"

World::World(const std::string& name)
{
	m_World = std::make_unique<tson::World>();
	m_CurrentMap = std::make_unique<Map>();

	SLN_INFO("Parsing [%s] and preloading maps", name);
	Parse(name);

	PreloadMaps();
	LoadMap(0);
}

void World::Parse(const std::string& name)
{
	m_World->parse(fs::path("assets/maps/" + name));
}

void World::PreloadMaps()
{
	tson::Tileson parser;
	m_MapNb = m_World->loadMaps(&parser);
}

void World::LoadMap(int index)
{
	if (index < m_MapNb)
	{
		auto& map = m_World->getMaps()[index];
		tson::WorldMapData mapData = m_World->getMapData()[index];

		SLN_INFO("Loading map [%s]", mapData.fileName);
		m_CurrentMap->LoadStatic(map.get(), mapData.position);

		m_CurrentMapBorder.Left = mapData.position.x;
		m_CurrentMapBorder.Right = mapData.position.x + mapData.size.x;
		m_CurrentMapBorder.Top = -mapData.position.y;
		m_CurrentMapBorder.Bottom = -mapData.position.y - mapData.size.y;
	}
	else
	{
		SLN_ERROR("Cannot load map, index is out of range");
	}
}

void World::LoadNextMap(const glm::vec3& playerPosition)
{
	int mapIndex = 0;
	for (const auto& mapData : m_World->getMapData())
	{
		MapBorder borders;
		borders.Left = mapData.position.x;
		borders.Right = mapData.position.x + mapData.size.x;
		borders.Top = -mapData.position.y;
		borders.Bottom = -mapData.position.y - mapData.size.y;

		if (playerPosition.x > borders.Left
			&& playerPosition.x < borders.Right
			&& playerPosition.y < borders.Top
			&& playerPosition.y > borders.Bottom)
		{
			LoadMap(mapIndex);
			return;
		}

		mapIndex++;
	}
}

bool World::IsPlayerLeavingMap(const glm::vec3& playerPosition)
{
	return playerPosition.x > m_CurrentMapBorder.Right
		|| playerPosition.x < m_CurrentMapBorder.Left
		|| playerPosition.y < m_CurrentMapBorder.Bottom
		|| playerPosition.y > m_CurrentMapBorder.Top;
}