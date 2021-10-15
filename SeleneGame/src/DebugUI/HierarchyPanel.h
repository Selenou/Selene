#pragma once

#include "Selene.h"
#include "Panel.h"
#include <memory>

class HierarchyPanel : public Panel
{
	public:
		HierarchyPanel(std::shared_ptr<Selene::Scene> scene);
	public:
		virtual void Draw() override;
	private:
		std::weak_ptr<Selene::Scene> m_ActiveScene;
		Selene::Actor m_SelectedActor;
};