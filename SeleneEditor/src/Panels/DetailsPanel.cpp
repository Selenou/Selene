#include "DetailsPanel.h"
#include <imgui/imgui.h>

namespace Selene
{
	void DetailsPanel::Draw()
	{
		ImGui::Begin("Details");
		{
			ImGui::Text("Details");
		}
		ImGui::End();
	}
}