#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "EventSystem/WindowEvent.h"

namespace Selene 
{
	class Game
	{
	public:
		Game();
		virtual ~Game() {};
	public:
		void Run();
		void PushLayer(Layer* layer);
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<LayerStack> m_LayerStack;
		bool m_IsRunning = true;
	};

	Game* CreateGame();
}