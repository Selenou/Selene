#include "SandboxLayer.h"
#include "imgui.h"

//tmp
#include  <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

SandboxLayer::SandboxLayer() 
	: Layer("Sandbox")
{
	m_Camera = std::make_unique<Selene::Camera>();
	m_Camera->SetPerspective(45.0f);
	m_Camera->SetPosition({ 0.0f, 0.0f, 100.0f });
	m_Camera->SetRotation({ 0.0f, 0.0f, 0.0f });

	auto& window = Selene::Game::GetInstance().GetWindow();
	m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());

	float skyboxVertices[] =
	{
		// front
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		// top
		-1.0,  1.0,  1.0,
		1.0,  1.0,  1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0,
		// back
		1.0, -1.0, -1.0,
		-1.0, -1.0, -1.0,
		-1.0,  1.0, -1.0,
		1.0,  1.0, -1.0,
		// bottom
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, -1.0,  1.0,
		-1.0, -1.0,  1.0,
		// left
		-1.0, -1.0, -1.0,
		-1.0, -1.0,  1.0,
		-1.0,  1.0,  1.0,
		-1.0,  1.0, -1.0,
		// right
		1.0, -1.0,  1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		1.0,  1.0,  1.0
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

	// Skybox
	m_SkyboxPipeline = Selene::Pipeline::Create();
	Selene::VertexBufferLayout skyboxLayout = { { "a_Position", Selene::DataType::Float3 } };

	m_SkyboxVbo = Selene::VertexBuffer::Create(skyboxVertices, sizeof(skyboxVertices));
	m_SkyboxVbo->SetLayout(skyboxLayout);
	m_SkyboxPipeline->BindVertexBuffer(m_SkyboxVbo);

	m_SkyboxEbo = Selene::IndexBuffer::Create(indices, sizeof(indices));
	m_SkyboxPipeline->BindIndexBuffer(m_SkyboxEbo);

	m_SkyboxShader = Selene::Shader::Create("skybox.vert", "skybox.frag");
	m_TextureCubeMap = Selene::TextureCubeMap::Create("skybox/purple1024.png");

	// Mesh
	m_Mesh = std::make_shared<Selene::Mesh>("corgi/corgi.obj");
	//m_MeshTest = std::make_shared<Selene::Mesh>("assets/meshes/cube/cube.obj");
}

void SandboxLayer::Update(Selene::Timestep ts)
{
	Selene::RenderingEngine::PrepareNewFrame(*m_Camera);
	
	// Skybox
	glDepthMask(GL_FALSE);
	m_TextureCubeMap->Bind();
	m_SkyboxShader->Bind();
	glm::mat4 v = glm::mat4(glm::mat3(m_Camera->GetViewMatrix())); // from mat3 to mat4 : removes any translation, but keeps all rotation transformations so the user can still look around the scene
	glm::mat4 vp = m_Camera->GetProjectionMatrix() * v;
	m_SkyboxShader->SetUniform("u_ViewProjection", vp);
	Selene::RenderingEngine::Submit(m_SkyboxPipeline, m_SkyboxEbo->GetCount());
	glDepthMask(GL_TRUE);
	
	// Mesh
	Selene::RenderingEngine::SubmitMesh(m_Mesh);
	//Selene::RenderingEngine::SubmitMesh(m_MeshTest);
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

	ImGui::Begin("Debug");
		if (ImGui::Checkbox("Wireframe", &useWireframeMode))
		{
			glPolygonMode(GL_FRONT_AND_BACK, useWireframeMode ? GL_LINE : GL_FILL);
		}
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