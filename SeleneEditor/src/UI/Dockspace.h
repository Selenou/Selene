#pragma once

#include "EditorUI.h"
#include "Selene.h"
#include <vector>
#include <memory>

namespace Selene 
{
	class Dockspace : public EditorUI
	{
	public:
		Dockspace(std::shared_ptr<Scene> scene);
	public:
		virtual void Draw() override;
	private:
		void DrawPanels();
	private:
		std::vector<std::unique_ptr<EditorUI>> m_Panels;
	};
}