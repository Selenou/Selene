#include "ViewportPanel.h"
#include "Utils/IconsForkAwesome.h"
#include <imgui.h>

namespace Selene
{
	void ViewportPanel::Draw()
	{
		ImGui::Begin(ICON_FK_GAMEPAD " Viewport");
		{
			m_RenderingPanel.Draw();
		}
		ImGui::End();
	}
}