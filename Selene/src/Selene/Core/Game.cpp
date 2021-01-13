#include "slnpch.h"
#include "Game.h"
#include "Macro.h"
#include "Selene/Rendering/RenderingEngine.h"
#include "Selene/EventSystem/EventDispatcher.h"

namespace Selene 
{
	Game* Game::s_Instance = nullptr;

	Game::Game(RenderingAPI::API api)
	{
		SLN_ENGINE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Set this first because window creation will need this for creating its rendering context
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
			UpdateTimeStep();
			m_Window->PollEvents();
			Render();
		} 
	}

	void Game::Render()
	{
		RenderingEngine::Clear();
		m_LayerStack->Update(m_TimeStep);
		m_LayerStack->RenderUI();
		m_Window->SwapBuffers();
	}

	void Game::PushLayer(Layer* layer)
	{
		m_LayerStack->PushLayer(layer);
	}

	void Game::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(SLN_BIND_EVENT(Game::OnWindowClose));
		dispatcher.Dispatch<FramebufferResizeEvent>(SLN_BIND_EVENT(Game::OnFramebufferResize));

		m_LayerStack->HandleEvent(event);
	}

	bool Game::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	bool Game::OnFramebufferResize(FramebufferResizeEvent& e)
	{
		RenderingEngine::SetViewport(e.GetWidth(), e.GetHeight());
		Render(); //TODO : use a dedicated thread for rendering and get rid of this line
		return false;
	}

	void Game::UpdateTimeStep()
	{
		float time = Time::GetTime();
		m_TimeStep = time - m_LastFrameTime;
		m_LastFrameTime = time;
	}
}