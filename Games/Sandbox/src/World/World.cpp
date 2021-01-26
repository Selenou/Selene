#include "World.h"

void World::Generate()
{
	m_Chunk = std::make_unique<Chunk>();
	m_Chunk->Generate();
}

void World::Render()
{
	m_Chunk->Render();
}