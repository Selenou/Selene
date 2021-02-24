#pragma once

#include "Selene.h"
#include "EditorUI.h"
#include <memory>

namespace Selene 
{
	class HierarchyPanel : public EditorUI
	{
	public:
		HierarchyPanel(std::shared_ptr<Scene> scene);
	public:
		virtual void Draw() override;
	private:
		std::weak_ptr<Scene> m_ActiveScene;
		Actor m_SelectedActor;
	};
}