#include "HierarchyPanel.h"
#include "IconsForkAwesome.h"

#include <imgui.h>

HierarchyPanel::HierarchyPanel(std::shared_ptr<Selene::Scene> scene) : m_ActiveScene(scene)
{

}

void HierarchyPanel::Draw()
{
	ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoMove;

	ImVec2 windowPos = ImGui::GetWindowPos();
	float offset = 25.0f;
	float x = windowPos.x + offset;
	float y = windowPos.y + offset;
	ImVec2 panelPos = ImVec2(x, y);
	ImGui::SetNextWindowPos(panelPos, ImGuiCond_Always, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(300, 450), ImGuiCond_Always);
	ImGui::SetNextWindowBgAlpha(0.5f);

	ImGui::Begin(ICON_FK_BARS " Scene Hierarchy", nullptr, windowFlags); // Adjacent string literal tokens are concatenated, covered by [lex.phases]/6
	{
		Selene::Actor clickedActor;
		
		m_ActiveScene.lock()->GetRegistry().each([&](auto actorID)
		{
			// Draw each actor tree node
			Selene::Actor actor { actorID, m_ActiveScene.lock() };
			auto& name = actor.GetComponent<Selene::NameComponent>().Name;

			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
				/*ImGuiTreeNodeFlags_OpenOnDoubleClick |
				ImGuiTreeNodeFlags_OpenOnArrow |
				ImGuiTreeNodeFlags_SpanAvailWidth;*/

			if (m_SelectedActor == actor)
			{
				flags |= ImGuiTreeNodeFlags_Selected;
			}
					
			bool isOpen = ImGui::TreeNodeEx((void*)(uint64_t)actorID, flags, name.c_str());

			if (ImGui::IsItemClicked())
			{
				clickedActor = actor;
			}

			if (isOpen)
			{
				ImGui::TreePop();
			}
		});

		if (clickedActor.GetActorID() != entt::null)
		{
			m_SelectedActor = clickedActor;
		}
	}
	ImGui::End();

	/*windowPos = ImGui::GetWindowPos();
	x = windowPos.x + offset;
	y = windowPos.y + ImGui::GetContentRegionAvail().y - offset;
	panelPos = ImVec2(x, y);
	ImGui::SetNextWindowPos(panelPos, ImGuiCond_Always, ImVec2(0.0f, 1.0f));
	ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_Always);
	ImGui::SetNextWindowBgAlpha(0.5f);

	ImGui::Begin(ICON_FK_WRENCH " Inspector", nullptr, windowFlags);
	{
		//ImGui::Text("Details");
	}
	ImGui::End();*/
}