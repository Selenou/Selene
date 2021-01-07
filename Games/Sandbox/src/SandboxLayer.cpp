#include "SandboxLayer.h"
#include "imgui.h"

SandboxLayer::SandboxLayer() 
	: Layer("Sandbox"), m_Camera(-3.2f, 3.2f, -1.8f, 1.8f)
{
	m_Camera.SetPosition({ 0.2f, 0.2f, 0.0f });

	float vertices[] =
	{
		-1.0f,	-1.0f,	-1.0f,	0.583f,  0.771f,  0.014f,
		1.0f,	-1.0f,	-1.0f,	0.609f,  0.115f,  0.436f,
		1.0f,	1.0f,	-1.0f,	0.327f,  0.483f,  0.844f,
		-1.0f,	1.0f,	-1.0f,	0.822f,  0.569f,  0.201f,
		-1.0f,	-1.0f,	 1.0f,	0.435f,  0.602f,  0.223f,
		1.0f,	-1.0f,	 1.0f,	0.714f,  0.505f,  0.345f,
		1.0f,	1.0f,	1.0f,	0.225f,  0.587f,  0.040f,
		-1.0f,	1.0f,	1.0f,	0.982f,  0.099f,  0.879f
	};

	uint32_t indices[] =
	{
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
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

void SandboxLayer::Update(Selene::Timestep ts)
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

	auto stats = Selene::RenderingEngine::GetStats();

	ImGui::Begin("Rendering Stats");
		ImGui::Text("FPS : %i", (int)(1.0f / stats.ts.GetSeconds()));
		ImGui::Text("Frametime : %f ms", stats.ts.GetMilliseconds());
	ImGui::End();
}