#include "HierarchyPanel.h"
#include "Utils/IconsForkAwesome.h"

#include <imgui/imgui.h>


namespace Selene
{
	void HierarchyPanel::Draw()
	{
		ImGui::Begin(ICON_FK_BARS " Scene Hierarchy"); // Adjacent string literal tokens are concatenated, covered by [lex.phases]/6
		{
			ImGuiIO& io = ImGui::GetIO();

			//ImGui::PushFont(io.Fonts->Fonts[1]);
			//ImGui::Text("Hierarchy ABCDE");
			//ImGui::PopFont();
		}
		ImGui::End();


		ImGui::Begin(ICON_FK_WRENCH " Details");
		{
			//ImGui::Text("Details");
		}
		ImGui::End();
	}
}