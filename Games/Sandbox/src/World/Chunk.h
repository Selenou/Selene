#pragma once

#include "Selene.h"

class Chunk
{
public:
	Chunk() = default;
public:
	void Generate();
	void Render();
private:
	std::array<std::shared_ptr<Selene::Mesh>, 4096> m_Mesh;
};