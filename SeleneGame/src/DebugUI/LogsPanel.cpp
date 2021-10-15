#include "LogsPanel.h"
#include "IconsForkAwesome.h"
#include "Selene.h"

void LogsPanel::Draw()
{
	ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoMove;

	ImVec2 windowtPos = ImGui::GetWindowPos();
	float offset = 25.0f;
	float x = windowtPos.x + offset;
	float y = windowtPos.y + ImGui::GetContentRegionAvail().y - offset;
	ImVec2 panelPos = ImVec2(x, y);
	ImGui::SetNextWindowPos(panelPos, ImGuiCond_Always, ImVec2(0.0f, 1.0f));
	ImGui::SetNextWindowBgAlpha(0.5f);

	ImGui::Begin(ICON_FK_TERMINAL " Logs", nullptr, windowFlags);
	{
		if (ImGui::Button("Clear"))
		{
			Selene::Logger::ClearLogs();
		}

		ImGui::SameLine();

		// Collapse : Simulate a toggle button
		static bool shouldCollapse = true;
		{
			bool shouldPopStyle = false;

			if (shouldCollapse)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
				shouldPopStyle = true;
			}

			if (ImGui::Button("Collapse"))
			{
				shouldCollapse = !shouldCollapse;
			}

			if ((shouldCollapse && shouldPopStyle) || shouldPopStyle)
			{
				ImGui::PopStyleColor(3);
			}
		}
				
		ImGui::BeginChild(ICON_FK_LIST" Console", ImVec2(1000, 200), false, ImGuiWindowFlags_HorizontalScrollbar);
		{
			for (auto& log : Selene::Logger::GetLogs())
			{
				ImVec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
				std::string icon = "";

				switch (log.first)
				{
					case Selene::LogSeverity::Trace:
						color = m_TraceColor;
						icon = ICON_FK_COMMENT;
						break;
					case Selene::LogSeverity::Info:
						color = m_InfoColor;
						icon = ICON_FK_INFO;
						break;
					case Selene::LogSeverity::Warning:
						color = m_WarnColor;
						icon = ICON_FK_EXCLAMATION_TRIANGLE;
						break;
					case Selene::LogSeverity::Error:
						color = m_ErrorColor;
						icon = ICON_FK_EXCLAMATION_CIRCLE;
						break;
					case Selene::LogSeverity::Critical:
						color = m_CriticalColor;
						icon = ICON_FK_BOLT;
						break;
				}

				ImGui::TextColored(color, (icon + " " + log.second).c_str());
			}

			if (shouldCollapse)
			{
				ImGui::SetScrollY(ImGui::GetScrollMaxY());
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();
}