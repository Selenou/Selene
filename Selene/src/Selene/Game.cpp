#include "slnpch.h"
#include "Game.h"

namespace Selene {

	Game::Game()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Game::~Game()
	{

	}

	void Game::Run()
	{
		while (m_IsRunning)
		{
			m_Window->Update();
		}
	}

}