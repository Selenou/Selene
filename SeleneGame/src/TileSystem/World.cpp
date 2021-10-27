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

		m_CurrentMapBounds.Left = mapData.position.x;
		m_CurrentMapBounds.Right = mapData.position.x + mapData.size.x;
		m_CurrentMapBounds.Top = -mapData.position.y;
		m_CurrentMapBounds.Bottom = -mapData.position.y - mapData.size.y + 8; // + 8 to cancel the fact that the map is 22.5 tiles high and not 23
	}
	else
	{
		SLN_ERROR("Cannot load map, index is out of range");
	}
}

void World::LoadNextMap(const glm::vec3& playerPosition/*, const glm::vec2& playerDirection*/)
{
	int mapIndex = 0;
	for (const auto& mapData : m_World->getMapData())
	{
		MapBounds bounds;
		bounds.Left = mapData.position.x;
		bounds.Right = mapData.position.x + mapData.size.x;
		bounds.Top = -mapData.position.y;
		bounds.Bottom = -mapData.position.y - mapData.size.y + 8; // + 8 to cancel the fact that the map is 22.5 tiles high and not 23

		if (playerPosition.x > bounds.Left
			&& playerPosition.x < bounds.Right
			&& playerPosition.y < bounds.Top
			&& playerPosition.y > bounds.Bottom)
		{
			LoadMap(mapIndex);
			return;
		}

		mapIndex++;
	}

	SLN_ERROR("Cannot load next map, mo match found");
}

bool World::IsPlayerLeavingMap(const glm::vec3& playerPosition)
{
	return playerPosition.x > m_CurrentMapBounds.Right
		|| playerPosition.x < m_CurrentMapBounds.Left
		|| playerPosition.y < m_CurrentMapBounds.Bottom
		|| playerPosition.y > m_CurrentMapBounds.Top;
}