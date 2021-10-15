#pragma once

#include "Panel.h"
#include <imgui.h>

class LogsPanel : public Panel
{
	public:
		virtual void Draw() override;
	private:
		ImVec4 m_TraceColor		= { 1.0f, 1.0f, 1.0f, 1.0f };
		ImVec4 m_InfoColor		= { 0.2f, 0.8f, 0.2f, 1.0f };
		ImVec4 m_WarnColor		= { 0.8f, 0.8f, 0.2f, 1.0f };
		ImVec4 m_ErrorColor		= { 0.8f, 0.2f, 0.2f, 1.0f };
		ImVec4 m_CriticalColor	= { 0.8f, 0.2f, 0.2f, 1.0f };
};