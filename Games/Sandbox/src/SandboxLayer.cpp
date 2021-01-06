#include "SandboxLayer.h"
#include "imgui.h"

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

	m_Pipeline = Selene::RenderingPipeline::Create();
	m_Pipeline->SetVertexBuffer(m_Vbo);
	m_Pipeline->SetIndexBuffer(m_Ebo);

	m_Shader = Selene::Shader::Create("base.vert", "base.frag");
}

void SandboxLayer::Update()
{
	Selene::RenderingEngine::PrepareNewFrame(m_Camera);
	Selene::RenderingEngine::Submit(m_Pipeline, m_Shader);
}

void SandboxLayer::RenderUI()
{
	auto info = Selene::RenderingEngine::GetAPIInfo();

	ImGui::Begin("Rendering Info");
		ImGui::Text("API : %s", info.API.c_str());
		ImGui::Text("Vendor : %s", info.Vendor.c_str());
		ImGui::Text("Renderer : %s", info.Renderer.c_str());
		ImGui::Text("Version : %s", info.Version.c_str());
		ImGui::Text("Shading Language Version : %s", info.ShadingLanguageVersion.c_str());
	ImGui::End();
}