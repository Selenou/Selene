#include "slnpch.h"
#include "Game.h"
#include "Macro.h"
#include "EventSystem/EventDispatcher.h"

namespace Selene 
{
	Game* Game::s_Instance = nullptr;

	Game::Game()
	{
		if (s_Instance != nullptr)
		{
			SLN_ENGINE_CRITICAL("Application already exists!");
		}

		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create()); 
		m_Window->SetEventCallback(SLN_BIND_EVENT(Game::OnEvent));

		m_LayerStack = std::make_unique<LayerStack>();
	}

	void Game::Run()
	{
		while (m_IsRunning)
		{
			m_LayerStack->Update();
			m_LayerStack->RenderUI();

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
	}

	bool Game::OnWindowClose(WindowCloseEvent & e)
	{
		m_IsRunning = false;
		return true;
	}
}