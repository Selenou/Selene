#pragma once

#include "Map.h"

#pragma warning(disable : 4267 4018 4244)
#include <tileson.hpp>
#pragma warning(default : 4267 4018 4244)

class World
{
public:
	World(const std::string& name);
public:
	void Update(Selene::Actor& player);
	inline Map* GetCurrentMap() { return m_CurrentMap.get(); }
private:
	void Parse(const std::string& name);
	void PreloadMaps();
	void LoadMap(int index);
	bool IsPlayerLeavingMap(const glm::vec3& playerPosition);
private:
	std::unique_ptr<tson::World> m_World;
	std::unique_ptr<Map> m_CurrentMap;
	int m_MapNb = 0;
	std::array<int, 4> m_CurrentMapBorder; // lrtb
};