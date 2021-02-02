#pragma once

namespace WorldConfig
{
	inline constexpr int CHUNK_SIZE					= 128;
	inline constexpr int CHUNK_HEIGHT				= 64;
	inline constexpr int DYNAMIC_WORLD_RADIUS		= 4; 
	inline constexpr float CHUNK_DISTANCE_THRESHOLD	= DYNAMIC_WORLD_RADIUS * 1.1f;
}