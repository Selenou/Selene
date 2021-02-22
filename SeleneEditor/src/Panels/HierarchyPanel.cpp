#include "HierarchyPanel.h"
#include <imgui/imgui.h>

namespace Selene
{
	void HierarchyPanel::Draw()
	{
		ImGui::Begin("Scene Hierarchy");
		{
			ImGui::Text("Hierarchy");
		}
		ImGui::End();
	}
}