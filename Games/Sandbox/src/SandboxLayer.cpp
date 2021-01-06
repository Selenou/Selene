#include "SandboxLayer.h"

SandboxLayer::SandboxLayer() 
	: Layer("Sandbox"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	m_Camera.SetPosition({ 0.2f, 0.2f, 0.0f });

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

void SandboxLayer::Update()
{
	m_Pipeline->Bind();

	m_Shader->Bind();
	m_Shader->SetUniform("u_ViewProjection", m_Camera.GetViewProjectionMatrix());

	Selene::RenderingEngine::DrawIndexed(m_Ebo->GetCount());
}