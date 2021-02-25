#include "LogsPanel.h"
#include "Utils/IconsForkAwesome.h"
#include "Selene.h"

namespace Selene
{
	void LogsPanel::Draw()
	{
		ImGui::Begin(ICON_FK_TERMINAL " Logs");
		{
			if (ImGui::Button("Clear"))
			{
				Logger::ClearLogs();
			}
				
			ImGui::BeginChild(ICON_FK_LIST" Console", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
			{
				for (auto& log : Logger::GetLogs())
				{
					ImVec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
					std::string icon = "";

					switch (log.first)
					{
					case LogSeverity::Trace:
						color = m_TraceColor;
						icon = ICON_FK_COMMENT;
						break;
					case LogSeverity::Info:
						color = m_InfoColor;
						icon = ICON_FK_INFO;
						break;
					case LogSeverity::Warning:
						color = m_WarnColor;
						icon = ICON_FK_EXCLAMATION_TRIANGLE;
						break;
					case LogSeverity::Error:
						color = m_ErrorColor;
						icon = ICON_FK_EXCLAMATION_CIRCLE;
						break;
					case LogSeverity::Critical:
						color = m_CriticalColor;
						icon = ICON_FK_BOLT;
						break;
					}

					ImGui::TextColored(color, (icon + " " + log.second).c_str());
				}

				ImGui::SetScrollY(ImGui::GetScrollMaxY());
			}

			ImGui::EndChild();
		}

		ImGui::End();
	}
}