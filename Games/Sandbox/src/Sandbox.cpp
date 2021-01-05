#include <Selene.h>
#include "imgui/imgui.h"

//tmp + remove in premake
#include <glad/glad.h>
#include "Selene/Rendering/Shader.h"
#include "Selene/Rendering/Buffer.h"

class SandboxLayer : public Selene::Layer
{
public:
	SandboxLayer() : Layer("Sandbox") 
	{
		float vertices[] = 
		{
			 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
		};

		uint32_t indices[] = 
		{
			0, 1, 3,
			1, 2, 3
		};

		m_Vbo = Selene::VertexBuffer::Create(vertices, sizeof(vertices));
		m_Ebo = Selene::IndexBuffer::Create(indices, sizeof(indices));
		
		Selene::VertexBufferLayout layout = 
		{ 
			{ "a_Position", Selene::DataType::Float3 },
			{ "a_Color", Selene::DataType::Float3 },
		};

		m_Vbo->SetLayout(layout);

		m_Pipeline = Selene::RenderingPipeline::Create(layout);
		m_Pipeline->SetVertexBuffer(m_Vbo);
		m_Pipeline->SetIndexBuffer(m_Ebo);

		m_Shader = Selene::Shader::Create("base.vert", "base.frag");
	}
public:
	virtual void Update() override 
	{
		m_Pipeline->Bind();
		m_Shader->Bind();
		Selene::RenderingEngine::DrawIndexed(m_Ebo->GetCount());
	}

	virtual void RenderUI() override {}

	std::shared_ptr<Selene::Shader> m_Shader;
	std::shared_ptr<Selene::VertexBuffer> m_Vbo;
	std::shared_ptr<Selene::IndexBuffer> m_Ebo;
	std::shared_ptr<Selene::RenderingPipeline> m_Pipeline;
};

class Sandbox : public Selene::Game
{
public:
	Sandbox(Selene::RenderingAPI::API renderingAPI)
		: Game(renderingAPI)
	{
		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{
	}
};

Selene::Game* Selene::CreateGame() 
{
	return new Sandbox(Selene::RenderingAPI::API::OpenGL);
}