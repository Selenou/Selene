#pragma once

namespace Selene
{
	class Config
	{
	public:
		static constexpr int DEFAULT_WINDOW_WIDTH = 1920;
		static constexpr int DEFAULT_WINDOW_HEIGHT = 1080;
		static constexpr char* DEFAULT_WINDOW_NAME = "Selene Engine";
		static constexpr bool VSYNC_ENABLED = true;
		static constexpr bool MIPMAP_ENABLED = false;
	};
}