#include "EditorLayer.h"
#include "Panels/RenderingPanel.h"
#include "Panels/HierarchyPanel.h"
#include "Panels/ConsolePanel.h"
#include "Panels/DetailsPanel.h"

#include <imgui/imgui.h>

namespace Selene
{
	EditorLayer::EditorLayer()
		: Layer("Editor")
	{
		auto& window = Game::GetInstance().GetWindow();

		m_Camera = std::make_unique<Camera>();
		m_Camera->SetOrthographic(2.0f);
		m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());

		//m_Panels.emplace_back(std::make_unique<RenderingPanel>());
		m_Panels.emplace_back(std::make_unique<HierarchyPanel>());
		m_Panels.emplace_back(std::make_unique<ConsolePanel>());
		m_Panels.emplace_back(std::make_unique<DetailsPanel>());

		m_Scene = std::make_shared<Scene>();

		Actor cadence = m_Scene->CreateActor("CadenceBackgroundMusic");
		auto& sourceComponent = cadence.AddComponent<AudioSourceComponent>(*(AudioEngine::CreateAudioSource("assets/sounds/fairy.wav")));
		//sourceComponent.Source.SetIsLooping(true);
		//sourceComponent.Source.Play();
	}

	void EditorLayer::Update(Timestep ts)
	{
		m_Camera->Update(ts);
	}

	void EditorLayer::Render()
	{
		RenderingEngine::BeginFrame(*m_Camera);
		{
		
		}
		RenderingEngine::EndFrame();
	}

	void EditorLayer::RenderUI()
	{
		// Dockspace
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar |
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse | 
			ImGuiWindowFlags_NoResize | 
			ImGuiWindowFlags_NoMove | 
			ImGuiWindowFlags_NoBringToFrontOnFocus | 
			ImGuiWindowFlags_NoNavFocus;
        
        ImGui::Begin("Selene Editor DockSpace", nullptr, window_flags);
        ImGui::PopStyleVar(3);

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("DockSpace");
            ImGui::DockSpace(dockspace_id);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Test"))
				{ 
					
				}
                ImGui::EndMenu();
            }

			if (ImGui::BeginMenu("About"))
			{
				if (ImGui::MenuItem("Test"))
				{

				}
				ImGui::EndMenu();
			}

            ImGui::EndMenuBar();
        }

        ImGui::End();


		for (auto& panel : m_Panels)
		{
			panel->Draw();
		}
	}

	void EditorLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<FramebufferResizeEvent>([=](FramebufferResizeEvent& e)
		{
			m_Camera->SetViewportSize(e.GetWidth(), e.GetHeight());
			return false;
		});
	}
}