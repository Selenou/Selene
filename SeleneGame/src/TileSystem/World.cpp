#include "World.h"

World::World(const std::string& name)
{
	m_World = std::make_unique<tson::World>();
	m_CurrentMap = std::make_unique<Map>();
	m_CurrentMapBorder = { 0, 0, 0, 0 };

	SLN_INFO("Parsing [%s] and preloading maps", name);
	Parse(name);
	PreloadMaps();
}

void World::Update(Selene::Actor& player)
{
	glm::vec3 playerPosition = player.GetComponent<Selene::TransformComponent>().Position;

	if(IsPlayerLeavingMap(playerPosition))
	{
		int mapIndex = 0;
		for (const auto& mapData : m_World->getMapData())
		{
			if (playerPosition.x > mapData.position.x 
				&& playerPosition.x < mapData.position.x + mapData.size.x
				&& playerPosition.y < -mapData.position.y
				&& playerPosition.y > -mapData.position.y - mapData.size.y)
			{
				LoadMap(mapIndex);
				return;
			}

			mapIndex++;
		}
	}
}

void World::Parse(const std::string& name)
{
	m_World->parse(fs::path("assets/maps/" + name));
}

void World::PreloadMaps()
{
	tson::Tileson parser;
	m_MapNb = m_World->loadMaps(&parser);

	LoadMap(0);
}

void World::LoadMap(int index)
{
	if (index < m_MapNb)
	{
		auto& map = m_World->getMaps()[index];
		tson::WorldMapData mapData = m_World->getMapData()[index];

		SLN_INFO("Loading map [%s]", mapData.fileName);
		m_CurrentMap->LoadStatic(map.get(), mapData.position);

		// TODO : 
		// refactor LoadStatic()
		// refactor border computation
		// proper camera system

		m_CurrentMapBorder = // y is reversed to match opengl coord system
		{
			mapData.position.x,
			mapData.position.x + mapData.size.x,
			-mapData.position.y,
			-mapData.position.y - mapData.size.y
		};
	}
	else
	{
		SLN_ERROR("Cannot load map, index is out of range");
	}
}

bool World::IsPlayerLeavingMap(const glm::vec3& playerPosition)
{
	return playerPosition.x > m_CurrentMapBorder[1]
		|| playerPosition.x < m_CurrentMapBorder[0]
		|| playerPosition.y < m_CurrentMapBorder[3]
		|| playerPosition.y > m_CurrentMapBorder[2];
}
