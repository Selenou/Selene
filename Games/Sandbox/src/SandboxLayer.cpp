#include "SandboxLayer.h"
#include "imgui.h"

//tmp
#include  <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Sandbox
{
	SandboxLayer::SandboxLayer()
		: Layer("Sandbox")
	{
		m_Camera = std::make_unique<Selene::Camera>();
		m_Camera->SetPerspective(45.0f, 0.01f, 10000.0f);
		m_Camera->SetPosition({ 0.0f, 10.0f, 10.0f });

		auto& window = Selene::Game::GetInstance().GetWindow();
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

			m_SkyboxShader = Selene::RenderingEngine::GetShaderLibrary()->Get("skybox");
			m_TextureCubeMap = Selene::TextureCubeMap::Create("assets/textures/skybox/purple1024.png");
		}

		// World
		Selene::RenderingEngine::GetShaderLibrary()->Load("chunk", "chunk.vert", "chunk.frag");
		m_World = std::make_unique<World>();
		m_World->GenerateChunks();
	}

	void SandboxLayer::Update(Selene::Timestep ts)
	{
		m_Camera->Update(ts);
		Selene::RenderingEngine::BeginFrame(*m_Camera);

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

		m_World->Render();

		Selene::RenderingEngine::EndFrame();
	}

	void SandboxLayer::RenderUI()
	{
		auto info = Selene::RenderingEngine::GetAPIInfo();
		auto stats = Selene::RenderingEngine::GetStats();

		static bool openRenderingStats = true;

		ImGuiWindowFlags windowFlags =
			ImGuiWindowFlags_NoDecoration |
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoFocusOnAppearing |
			ImGuiWindowFlags_NoNav |
			ImGuiWindowFlags_NoMove;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 workAreaPos = viewport->GetWorkPos();
		ImVec2 windowPos = ImVec2(workAreaPos.x + viewport->GetWorkSize().x - 10.0f, workAreaPos.y + 10.0f);
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, ImVec2(1.0f, 0.0f));
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::SetNextWindowBgAlpha(0.15f);



		// Fps average each second
		
		static int s_AverageFps;
		static int s_FrameCounter;
		static float s_FrametimeSum;

		s_FrametimeSum += stats.Ts.GetSeconds();
		s_FrameCounter++;

		if(s_FrametimeSum > 1.0f)
		{
			s_AverageFps = s_FrameCounter;

			s_FrameCounter = 0;
			s_FrametimeSum = 0.0f;
		}


		ImGui::Begin("Rendering", &openRenderingStats, windowFlags);
		ImGui::Text("FPS : %i", s_AverageFps);
		ImGui::Text("Frametime : %f ms", stats.Ts.GetMilliseconds());
		ImGui::Text("Draw calls : %i", stats.DrawCalls);
		ImGui::Text("Vertex Count : %i", stats.TotalVertexCount);
		ImGui::Text("Index Count : %i", stats.TotalIndexCount);
		ImGui::Separator();
		ImGui::Text("API : %s", info.API.c_str());
		ImGui::Text("Vendor : %s", info.Vendor.c_str());
		ImGui::Text("Renderer : %s", info.Renderer.c_str());
		ImGui::Text("Version : %s", info.Version.c_str());
		ImGui::Text("Shading Language Version : %s", info.ShadingLanguageVersion.c_str());
		ImGui::End();

		ImGui::Begin("Debug");
		static bool useWireframeMode = false;
		if (ImGui::Checkbox("Wireframe", &useWireframeMode))
		{
			glPolygonMode(GL_FRONT_AND_BACK, useWireframeMode ? GL_LINE : GL_FILL);
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
		dispatcher.Dispatch<Selene::MousePositionMoveEvent>([=](Selene::MousePositionMoveEvent& e)
			{
				m_Camera->UpdateMousePosition(e.GetX(), e.GetY());
				return false;
			});
	}

}