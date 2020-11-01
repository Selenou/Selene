#pragma once

#include "Window.h"

namespace Selene {

	class Game
	{
	public:
		Game();
		virtual ~Game();
	public:
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};

	Game* CreateGame();
}