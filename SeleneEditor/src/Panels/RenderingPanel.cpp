#include "RenderingPanel.h"
#include "Selene.h"
#include "Utils/IconsForkAwesome.h"
#include <imgui/imgui.h>

namespace Selene
{
	void RenderingPanel::Draw()
	{
		auto info = RenderingEngine::GetAPIInfo();
		auto stats = RenderingEngine::GetStats();

		ImGuiWindowFlags windowFlags =
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoFocusOnAppearing |
			ImGuiWindowFlags_NoNav |
			ImGuiWindowFlags_NoMove;

		ImVec2 windowtPos = ImGui::GetWindowPos();
		float x = windowtPos.x + ImGui::GetContentRegionAvail().x;
		float y = windowtPos.y + (ImGui::GetWindowSize().y - ImGui::GetContentRegionAvail().y);
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
			ImGui::Text("Vendor : %s", info.Vendor.c_str());
			ImGui::Text("Renderer : %s", info.Renderer.c_str());
			ImGui::Text("Version : %s", info.Version.c_str());
			ImGui::Text("Shading Language Version : %s", info.ShadingLanguageVersion.c_str());
		}
		ImGui::End();
	}
}