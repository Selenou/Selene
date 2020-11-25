#include "slnpch.h"
#include "Game.h"
#include "Macro.h"
#include "Selene/Rendering/RenderingEngine.h"
#include "EventSystem/EventDispatcher.h"

#include <glad/glad.h>

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




		//tmp
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		uint32_t indices[] = {
			0, 1, 3,
			1, 2, 3
		};
	
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		m_Vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		m_Vbo->Bind();

		m_Ebo = IndexBuffer::Create(indices, sizeof(indices)); 
		m_Ebo->Bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		m_Shader = Shader::Create("base.vert", "base.frag");
	}

	void Game::Run()
	{
		while (m_IsRunning)
		{
			RenderingEngine::Clear();
			



			//tmp
			m_Shader->Bind();
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);




			m_LayerStack->Update();
			m_LayerStack->RenderUI();

			m_Window->Update();
		}
	}

	void Game::PushLayer(Layer* layer)
	{
		m_LayerStack->PushLayer(layer);
	}

	void Game::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SLN_BIND_EVENT(Game::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SLN_BIND_EVENT(Game::OnWindowResize));
		dispatcher.Dispatch<FramebufferResizeEvent>(SLN_BIND_EVENT(Game::OnFramebufferResize));
	}

	bool Game::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	bool Game::OnWindowResize(WindowResizeEvent& e)
	{
		// TODO : Manage minimized
		return false;
	}

	bool Game::OnFramebufferResize(FramebufferResizeEvent& e)
	{
		RenderingEngine::SetViewport(e.GetWidth(), e.GetHeight());
		return true;
	}
}