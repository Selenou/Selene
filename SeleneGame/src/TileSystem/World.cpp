#include "World.h"

World::World(const std::string& name)
{
	m_World = std::make_unique<tson::World>();
	m_CurrentMap = std::make_unique<Map>();

	SLN_INFO("Parsing [%s] and preloading maps", name);
	Parse(name);
	PreloadMaps();
}

void World::Update(Selene::Actor& player)
{
	glm::vec3 playerPosition = player.GetComponent<Selene::TransformComponent>().Position;

	if (playerPosition.x > r)
		LoadMap(1);
	if (playerPosition.x < l)
		LoadMap(0);

	if (playerPosition.y < b)
		LoadMap(2);
	if (playerPosition.y > t)
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

	LoadMap(0);
}

void World::LoadMap(int index)
{
	if (index < m_MapNb)
	{
		auto& map = m_World->getMaps()[index];
		tson::WorldMapData mapData = m_World->getMapData()[index];
		//SLN_INFO("Loading map [%s]", mapData.fileName);
		m_CurrentMap->LoadStatic(map.get(), mapData.position);
		//SLN_INFO("Map [%s] is loaded", mapData.fileName);

		// TODO : bad value if y > 0, load map3 in infinite loop
		// use a container for those 4 values
		// refactor LoadStatic()
		// dont hardcode loadmap index, find the correct map to load
		// memory leak index/vertex buffer


		l = mapData.position.x;
		r = l + mapData.size.x;
		b = mapData.position.y;
		t = b + mapData.size.y;
	}
	else
	{
		SLN_ERROR("Cannot load map, index is out of range");
	}
}
