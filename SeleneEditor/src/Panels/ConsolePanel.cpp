#include "ConsolePanel.h"
#include <imgui/imgui.h>

namespace Selene
{
	void ConsolePanel::Draw()
	{
		ImGui::Begin("Console");
		{
			ImGui::Text("Console");
		}
		ImGui::End();
	}
}