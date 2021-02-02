#pragma once

namespace Selene
{
	namespace Config
	{
		inline constexpr int DEFAULT_WINDOW_WIDTH		= 1920; // C++17 : inline constexpr
		inline constexpr int DEFAULT_WINDOW_HEIGHT		= 1080;
		inline constexpr char* DEFAULT_WINDOW_NAME		= "Selene Engine";
		inline constexpr bool VSYNC_ENABLED				= false;
		inline constexpr bool MIPMAP_ENABLED			= true;
		inline constexpr bool DEPTH_BUFER_ENABLED		= true;
		inline constexpr bool FACE_CULLING_ENABLED		= false;
	};
}