#include "World.h"

namespace Sandbox
{
	void World::Generate()
	{
		m_Chunk = std::make_unique<Chunk>();
		m_Chunk->GenerateMesh();
	}

	void World::Render()
	{
		m_Chunk->Render();
	}
}