#include "ConsolePanel.h"
#include "Utils/IconsForkAwesome.h"
#include <imgui/imgui.h>

namespace Selene
{
	void ConsolePanel::Draw()
	{
		ImGui::Begin(ICON_FK_TERMINAL " Console");
		{
			
		}
		ImGui::End();
	}
}