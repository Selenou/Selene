#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "EventSystem/WindowEvent.h"
#include "Selene/Rendering/RenderingAPI.h"

#include "Selene/Rendering/Shader.h"
#include "Selene/Rendering/Buffer.h"


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
		void OnEvent(Event& e);
		inline Window& GetWindow() { return *m_Window; }
		inline static Game& GetInstance() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnFramebufferResize(FramebufferResizeEvent& e);
	private:


		//tmp
		unsigned int vao;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexBuffer> m_Vbo;
		std::shared_ptr<IndexBuffer> m_Ebo;


		std::unique_ptr<Window> m_Window;
		std::unique_ptr<LayerStack> m_LayerStack;
		bool m_IsRunning = true;
		static Game* s_Instance;
	};

	Game* CreateGame();
}