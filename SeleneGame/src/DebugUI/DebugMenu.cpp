#include "DebugMenu.h"
#include "IconsForkAwesome.h"
#include "GameLayer.h" // maybe change that later

#include <imgui.h>

void DebugMenu::Draw()
{
	ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNav;

	ImGui::SetNextWindowBgAlpha(0.5f);

	ImGui::Begin(ICON_FK_BUG " Debug Menu", nullptr, windowFlags);
	{
		ImGui::Checkbox("Show physics debug", &GameLayer::s_ShowPhysicsDebug);
	}
	ImGui::End();
}