#pragma once

namespace Selene
{
	namespace Config
	{
		constexpr int DEFAULT_WINDOW_WIDTH			= 1920; // C++17 : inline constexpr
		constexpr int DEFAULT_WINDOW_HEIGHT			= 1080;
		constexpr char* DEFAULT_WINDOW_NAME			= "Selene Engine";
		constexpr bool VSYNC_ENABLED				= false;
		constexpr bool MIPMAP_ENABLED				= false;
		constexpr bool TEXTURE_FILTERING_ENABLED	= false;
		constexpr bool DEPTH_BUFER_ENABLED			= true;
		constexpr bool FACE_CULLING_ENABLED			= true;
	};
}