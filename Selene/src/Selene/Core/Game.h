#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "Selene/Scene/Scene.h"
#include "Selene/Event/WindowEvent.h"
#include "Selene/Rendering/RenderingAPI.h"

namespace Selene 
{
	class Game
	{
	public:
		Game(RenderingAPI::API api);
		virtual ~Game();
	public:
		void Run();
		void PushLayer(Layer* layer);
		void OnEvent(Event& event);
		inline const Timestep& GetTimestep() { return m_TimeStep; }
		inline std::shared_ptr<Scene> GetActiveScene() { return m_ActiveScene; }
		inline Window& GetWindow() { return *m_Window; }
		inline static Game& GetInstance() { return *s_Instance; }
	private:
		void Update();
		void Render();
		void UpdateTimeStep();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnFramebufferResize(FramebufferResizeEvent& e);
	private:
		static inline Game* s_Instance = nullptr;
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<LayerStack> m_LayerStack;
		std::shared_ptr<Scene> m_ActiveScene;
		bool m_IsRunning = true;
		Timestep m_TimeStep;
		float m_LastFrameTime = 0.0f;
	};

	Game* CreateGame();
}