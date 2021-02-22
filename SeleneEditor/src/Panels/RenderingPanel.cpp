#include "slnpch.h"
#include "RenderingPanel.h"
#include "Selene.h"
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

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 workAreaPos = viewport->GetWorkPos();
		ImVec2 windowPos = ImVec2(workAreaPos.x + viewport->GetWorkSize().x - 10.0f, workAreaPos.y + 10.0f);
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, ImVec2(1.0f, 0.0f));
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::SetNextWindowBgAlpha(0.15f);

		m_FrametimeSum += stats.Ts.GetSeconds();
		m_FrameCounter++;

		if (m_FrametimeSum > 1.0f)
		{
			m_AverageFps = m_FrameCounter;

			m_FrameCounter = 0;
			m_FrametimeSum = 0.0f;
		}

		ImGui::Begin("Rendering Info", nullptr, windowFlags);
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