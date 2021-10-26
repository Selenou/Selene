#pragma once

#include "Map.h"

#pragma warning(disable : 4267 4018 4244)
#include <tileson.hpp>
#pragma warning(default : 4267 4018 4244)

struct MapBorder
{
	int Left;
	int Right;
	int Top;
	int Bottom;
};

class World
{
public:
	World(const std::string& name);
public:
	inline Map* GetCurrentMap() { return m_CurrentMap.get(); }
	inline const MapBorder& GetCurrentMapBorder() { return m_CurrentMapBorder; }
	bool IsPlayerLeavingMap(const glm::vec3& playerPosition);
	void LoadNextMap(const glm::vec3& playerPosition);
private:
	void Parse(const std::string& name);
	void PreloadMaps();
	void LoadMap(int index);
private:
	std::unique_ptr<tson::World> m_World;
	std::unique_ptr<Map> m_CurrentMap;
	int m_MapNb = 0;
	MapBorder m_CurrentMapBorder = { 0, 0, 0, 0 };
};