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
		inline Window& GetWindow() { return *m_Window; }
		inline static Game& GetInstance() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<LayerStack> m_LayerStack;
		bool m_IsRunning = true;
	private:
		static Game* s_Instance;
	};

	Game* CreateGame();
}