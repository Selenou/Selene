#include "slnpch.h"
#include "Game.h"
#include "Macro.h"
#include "Selene/Rendering/RenderingEngine.h"
#include "EventSystem/EventDispatcher.h"

namespace Selene 
{
	Game* Game::s_Instance = nullptr;

	Game::Game(RenderingAPI::API api)
	{

		SLN_ENGINE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Set this first because window creation will need this for creating its rendering contexts
		RenderingAPI::SetAPI(api);

		m_Window = std::unique_ptr<Window>(Window::Create()); 
		m_Window->SetEventCallback(SLN_BIND_EVENT(Game::OnEvent));

		RenderingEngine::Init();

		m_LayerStack = std::make_unique<LayerStack>();
	}

	void Game::Run()
	{
		while (m_IsRunning)
		{
			RenderingEngine::Clear();

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