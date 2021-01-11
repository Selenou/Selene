#include "SandboxLayer.h"
#include "imgui.h"

SandboxLayer::SandboxLayer() 
	: Layer("Sandbox")
{
	m_Camera = std::make_unique<Selene::Camera>();
	m_Camera->SetPerspective(45.0f);
	m_Camera->SetPosition({ 0.0f, 0.0f, 10.0f });
	m_Camera->SetRotation({ 0.0f, 0.0f, 0.0f });

	// Could be better here
	auto& window = Selene::Game::GetInstance().GetWindow();
	m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());
	
	float vertices[] =
	{
		// front
		-1.0, -1.0,  1.0, 0.0, 0.0,
		1.0, -1.0,  1.0, 1.0, 0.0,
		1.0,  1.0,  1.0, 1.0, 1.0,
		-1.0,  1.0,  1.0, 0.0, 1.0,
		// top
		-1.0,  1.0,  1.0, 0.0, 0.0,
		1.0,  1.0,  1.0, 1.0, 0.0,
		1.0,  1.0, -1.0, 1.0, 1.0,
		-1.0,  1.0, -1.0, 0.0, 1.0,
		// back
		1.0, -1.0, -1.0, 0.0, 0.0,
		-1.0, -1.0, -1.0, 1.0, 0.0,
		-1.0,  1.0, -1.0, 1.0, 1.0,
		1.0,  1.0, -1.0, 0.0, 1.0,
		// bottom
		-1.0, -1.0, -1.0, 0.0, 0.0,
		1.0, -1.0, -1.0, 1.0, 0.0,
		1.0, -1.0,  1.0, 1.0, 1.0,
		-1.0, -1.0,  1.0, 0.0, 1.0,
		// left
		-1.0, -1.0, -1.0, 0.0, 0.0,
		-1.0, -1.0,  1.0, 1.0, 0.0,
		-1.0,  1.0,  1.0, 1.0, 1.0,
		-1.0,  1.0, -1.0,0.0, 1.0,
		// right
		1.0, -1.0,  1.0, 0.0, 0.0,
		1.0, -1.0, -1.0, 1.0, 0.0,
		1.0,  1.0, -1.0, 1.0, 1.0,
		1.0,  1.0,  1.0, 0.0, 1.0
	};

	uint32_t indices[] =
	{
		// front
		0, 1, 2,
		2, 3, 0, 
		// top
		4,  5, 6,
		6,  7, 4,
		// back
		8,  9, 10,
		10, 11, 8,
		// bottom
		12, 13, 14,
		14, 15, 12,
		// left
		16, 17, 18,
		18, 19, 16,
		// right
		20, 21, 22,
		22, 23, 20 
	};

	m_Vbo = Selene::VertexBuffer::Create(vertices, sizeof(vertices));
	m_Ebo = Selene::IndexBuffer::Create(indices, sizeof(indices));

	Selene::VertexBufferLayout layout =
	{
		{ "a_Position", Selene::DataType::Float3 },
		{ "a_TexCoord", Selene::DataType::Float2 }
	};

	m_Vbo->SetLayout(layout);

	m_Pipeline = Selene::RenderingPipeline::Create();
	m_Pipeline->SetVertexBuffer(m_Vbo);
	m_Pipeline->SetIndexBuffer(m_Ebo);

	m_Shader = Selene::Shader::Create("base.vert", "base.frag");
	m_Texture = Selene::Texture::Create("corgi.jpg");

	m_Shader->Bind();
	m_Shader->SetUniform("u_Texture", 0);
	m_Shader->Unbind();
}

void SandboxLayer::Update(Selene::Timestep ts)
{
	Selene::RenderingEngine::PrepareNewFrame(*m_Camera);
	m_Texture->Bind();
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


	// Debug
	ImGui::Begin("Camera Settings");
		if (ImGui::SliderAngle("RotationX", &m_Camera->GetRotation()[0]))
		{
			m_Camera->SetRotation(m_Camera->GetRotation());
		}
		if (ImGui::SliderAngle("RotationY", &m_Camera->GetRotation()[1]))
		{
			m_Camera->SetRotation(m_Camera->GetRotation());
		}
		if (ImGui::SliderAngle("RotationZ", &m_Camera->GetRotation()[2]))
		{
			m_Camera->SetRotation(m_Camera->GetRotation());
		}

		if (ImGui::Checkbox("UsePerspective", &usePerspective))
		{
			if (usePerspective)
			{
				m_Camera->SetPerspective(45.0f);
				m_Camera->SetPosition({ 0.0f, 0.0f, 10.0f });
			}
			else
			{
				m_Camera->SetOrthographic(5.0f);
				m_Camera->SetPosition({ 0.0f, 0.0f, 0.0f });
			}
		}
	ImGui::End();
}

void SandboxLayer::OnEvent(Selene::Event& event)
{
	Selene::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Selene::FramebufferResizeEvent>([=](Selene::FramebufferResizeEvent& e)
	{
		m_Camera->SetViewportSize(e.GetWidth(), e.GetHeight());
		return false;
	});
}