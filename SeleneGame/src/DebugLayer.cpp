#include "DebugLayer.h"
#include "DebugUI/IconsForkAwesome.h"
#include "DebugUI/RenderingPanel.h"
#include "DebugUI/HierarchyPanel.h"
#include "DebugUI/LogsPanel.h"

#include <imgui.h>

DebugLayer::DebugLayer() : Layer("Debug")
{
	ImGuiIO& io = ImGui::GetIO();

	io.FontDefault = io.Fonts->AddFontDefault();
	ImFontConfig config;
	config.MergeMode = true;
	config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
	static const ImWchar icon_ranges[] = { ICON_MIN_FK, ICON_MAX_FK, 0 };
	io.Fonts->AddFontFromFileTTF("assets/fonts/forkawesome/forkawesome-webfont.ttf", 13.0f, &config, icon_ranges);

	m_Panels.emplace_back(std::make_unique<RenderingPanel>());
	m_Panels.emplace_back(std::make_unique<HierarchyPanel>(Selene::Game::GetInstance().GetActiveScene()));
	m_Panels.emplace_back(std::make_unique<LogsPanel>());
}

void DebugLayer::RenderUI()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->GetWorkPos());
	ImGui::SetNextWindowSize(viewport->GetWorkSize());
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Selene Debug", nullptr, window_flags);
	{
		for (auto& panel : m_Panels)
		{
			panel->Draw();
		}
	}
	ImGui::End();

	ImGui::PopStyleVar(3);
}