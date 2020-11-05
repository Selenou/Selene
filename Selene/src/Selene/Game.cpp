#include "slnpch.h"
#include "Game.h"
#include "Macro.h"
#include "EventSystem/EventDispatcher.h"

namespace Selene 
{
	Game::Game()
	{
		m_LayerStack = std::make_unique<LayerStack>();

		m_Window = std::unique_ptr<Window>(Window::Create()); 
		m_Window->SetEventCallback(SLN_BIND_EVENT(Game::OnEvent));
	}

	void Game::Run()
	{
		while (m_IsRunning)
		{
			m_LayerStack->Update();
			m_Window->Update();
		}
	}

	void Game::PushLayer(Layer * layer)
	{
		m_LayerStack->PushLayer(layer);
	}

	void Game::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SLN_BIND_EVENT(Game::OnWindowClose));

		// Debug
		SLN_ENGINE_WARN(e.ToString());
	}

	bool Game::OnWindowClose(WindowCloseEvent & e)
	{
		m_IsRunning = false;
		return true;
	}
}