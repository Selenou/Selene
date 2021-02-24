#include "HierarchyPanel.h"
#include "Utils/IconsForkAwesome.h"

#include <imgui/imgui.h>

namespace Selene
{

	HierarchyPanel::HierarchyPanel(std::shared_ptr<Scene> scene) : m_ActiveScene(scene)
	{

	}

	void HierarchyPanel::Draw()
	{
		ImGui::Begin(ICON_FK_BARS " Scene Hierarchy"); // Adjacent string literal tokens are concatenated, covered by [lex.phases]/6
		{
			static uint32_t selection_mask = -1;

			Actor clickedActor;

			m_ActiveScene.lock()->m_Registry.each([&](auto actorID)
			{
				// Draw each actor tree node
				Actor actor { actorID, m_ActiveScene.lock() };
				auto& name = actor.GetComponent<NameComponent>().Name;

				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick |
					ImGuiTreeNodeFlags_OpenOnArrow |
					ImGuiTreeNodeFlags_SpanAvailWidth;

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
					ImGui::Text("Hello there");
					ImGui::TreePop();
				}
			});

			if (clickedActor.GetActorID() != entt::null)
			{
				m_SelectedActor = clickedActor;
			}
		}
		ImGui::End();


		ImGui::Begin(ICON_FK_WRENCH " Details");
		{
			//ImGui::Text("Details");
		}
		ImGui::End();
	}
}