#pragma once

#include "Window.h"
#include "EventSystem/WindowEvent.h"

namespace Selene {

	class Game
	{
	public:
		Game();
		virtual ~Game();
	public:
		void Run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};

	Game* CreateGame();
}