#include "Dockspace.h"
#include "ViewportPanel.h"
#include "HierarchyPanel.h"
#include "LogsPanel.h"
#include "Utils/IconsForkAwesome.h"
#include <imgui/imgui.h>

namespace Selene
{
	Dockspace::Dockspace(std::shared_ptr<Scene> scene)
	{
		m_Panels.emplace_back(std::make_unique<ViewportPanel>());
		m_Panels.emplace_back(std::make_unique<HierarchyPanel>(scene));
		m_Panels.emplace_back(std::make_unique<LogsPanel>());
	}

	void Dockspace::Draw()
	{
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


		DrawPanels();
	}

	void Dockspace::DrawPanels()
	{
		for (auto& panel : m_Panels)
		{
			panel->Draw();
		}
	}
}