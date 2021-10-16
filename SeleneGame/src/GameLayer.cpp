#include "GameLayer.h"

//tmp
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GameLayer::GameLayer() : Layer("Game")
{
	auto& window = Selene::Game::GetInstance().GetWindow();

	m_Camera = std::make_unique<Selene::Camera>();
	//m_Camera->SetOrthographic(2.0f);
	m_Camera->SetPerspective(45.0f, 0.1f, 20000.0f);
	m_Camera->SetPosition({ 0.0f, 0.0f, 10000.0f });
	m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());

	// Skybox
	{
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

		m_SkyboxPipeline = Selene::Pipeline::Create();
		Selene::VertexBufferLayout skyboxLayout = { { "a_Position", Selene::DataType::Float3 } };

		m_SkyboxVbo = Selene::VertexBuffer::Create(skyboxVertices, sizeof(skyboxVertices));
		m_SkyboxVbo->SetLayout(skyboxLayout);
		m_SkyboxPipeline->BindVertexBuffer(m_SkyboxVbo);

		m_SkyboxEbo = Selene::IndexBuffer::Create(indices, sizeof(indices));
		m_SkyboxPipeline->BindIndexBuffer(m_SkyboxEbo);

		Selene::RenderingEngine::GetShaderLibrary()->Load("skybox", "skybox.vert", "skybox.frag");
		m_SkyboxShader = Selene::RenderingEngine::GetShaderLibrary()->Get("skybox");
		m_TextureCubeMap = Selene::TextureCubeMap::Create("assets/textures/skybox/purple1024.png");
	}

	Selene::Actor cadence = Selene::Game::GetInstance().GetActiveScene()->CreateActor("CadenceBackgroundMusic");
	auto& sourceComponent = cadence.AddComponent<Selene::AudioSourceComponent>(Selene::AudioEngine::CreateAudioSource("assets/sounds/fairy.wav"));
	sourceComponent.Source->SetIsLooping(true);
	//sourceComponent.Source->Play();

	Selene::Actor moon = Selene::Game::GetInstance().GetActiveScene()->CreateActor("MajoraMoon");
	moon.AddComponent<Selene::MeshComponent>(std::make_shared<Selene::Mesh>("moon/moon.obj"));
}

void GameLayer::Update(Selene::Timestep ts)
{
	m_Camera->Update(ts);
}

void GameLayer::Render()
{
	Selene::RenderingEngine::BeginFrame(*m_Camera);
	{
		// Skybox
		glDepthMask(GL_FALSE);
		glCullFace(GL_FRONT);
		m_TextureCubeMap->Bind();
		m_SkyboxShader->Bind();
		glm::mat4 v = glm::mat4(glm::mat3(m_Camera->GetViewMatrix())); // from mat3 to mat4 : removes any translation, but keeps all rotation transformations so the user can still look around the scene
		glm::mat4 vp = m_Camera->GetProjectionMatrix() * v;
		m_SkyboxShader->SetUniform("u_ViewProjection", vp);
		Selene::RenderingEngine::Submit(m_SkyboxPipeline, m_SkyboxEbo->GetCount(), m_SkyboxVbo->GetCount());
		glCullFace(GL_BACK);
		glDepthMask(GL_TRUE);

		auto meshView = Selene::Game::GetInstance().GetActiveScene()->GetRegistry().view<Selene::MeshComponent>();
		for (auto entity : meshView)
		{
			Selene::RenderingEngine::SubmitMesh(meshView.get<Selene::MeshComponent>(entity).Mesh);
		}
	}
	Selene::RenderingEngine::EndFrame();
}

void GameLayer::OnEvent(Selene::Event& event)
{
	Selene::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Selene::FramebufferResizeEvent>([=](Selene::FramebufferResizeEvent& e)
	{
		m_Camera->SetViewportSize(e.GetWidth(), e.GetHeight());
		return false;
	});

	dispatcher.Dispatch<Selene::MousePositionMoveEvent>([=](Selene::MousePositionMoveEvent& e)
	{
		m_Camera->UpdateMousePosition(e.GetX(), e.GetY());
		return false;
	});

	/*dispatcher.Dispatch<Selene::KeyPressEvent>([=](Selene::KeyPressEvent& e)
	{
		if (e.GetKeyCode() == Selene::Key::A)
			SLN_TRACE("A PRESSED");
		return false;
	});*/
}