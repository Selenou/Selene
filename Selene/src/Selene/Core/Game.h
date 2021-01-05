#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "Selene/EventSystem/WindowEvent.h"
#include "Selene/Rendering/RenderingAPI.h"

namespace Selene 
{
	class Game
	{
	public:
		Game(RenderingAPI::API api);
		virtual ~Game() {};
	public:
		void Run();
		void PushLayer(Layer* layer);
		void OnEvent(Event& event);
		inline Window& GetWindow() { return *m_Window; }
		inline static Game& GetInstance() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnFramebufferResize(FramebufferResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<LayerStack> m_LayerStack;
		bool m_IsRunning = true;
		static Game* s_Instance;
	};

	Game* CreateGame();
}