#include "RenderingPanel.h"
#include "Selene.h"
#include "IconsForkAwesome.h"
#include <imgui.h>

void RenderingPanel::Draw()
{
	auto info = Selene::RenderingEngine::GetAPIInfo();
	auto stats = Selene::RenderingEngine::GetStats();

	ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoMove;

	ImVec2 windowPos = ImGui::GetWindowPos();
	float offset = 25.0f;
	float x = windowPos.x + ImGui::GetContentRegionAvail().x - offset;
	float y = windowPos.y + offset;
	ImVec2 panelPos = ImVec2(x,y);
	ImGui::SetNextWindowPos(panelPos, ImGuiCond_Always, ImVec2(1.0f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.15f);

	m_FrametimeSum += stats.Ts.GetSeconds();
	m_FrameCounter++;

	if (m_FrametimeSum > 1.0f)
	{
		m_AverageFps = m_FrameCounter;

		m_FrameCounter = 0;
		m_FrametimeSum = 0.0f;
	}

	ImGui::Begin(ICON_FK_WRENCH " Rendering Stats", nullptr, windowFlags);
	{
		ImGui::Text("FPS : %i", m_AverageFps);
		ImGui::Text("Frametime : %f ms", stats.Ts.GetMilliseconds());
		ImGui::Text("Draw calls : %i", stats.DrawCalls);
		ImGui::Text("Vertex Count : %i", stats.TotalVertexCount);
		ImGui::Text("Index Count : %i", stats.TotalIndexCount);
	}
	ImGui::Separator();
	{
		ImGui::Text("API : %s", info.API.c_str());
		ImGui::Text("Version : %s", info.Version.c_str());
		ImGui::Text("Vendor : %s", info.Vendor.c_str());
		ImGui::Text("Renderer : %s", info.Renderer.c_str());
	}
	ImGui::End();
}