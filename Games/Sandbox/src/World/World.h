#pragma once

#include "Selene.h"
#include "Chunk.h"

namespace Sandbox
{
	class World
	{
	public:
		World() = default;
	public:
		void Generate();
		void Render();
	private:
		std::unique_ptr<Chunk> m_Chunk;
	};
}