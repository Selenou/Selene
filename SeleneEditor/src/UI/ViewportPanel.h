#pragma once

#include "EditorUI.h"
#include "RenderingPanel.h"

namespace Selene 
{
	class ViewportPanel : public EditorUI
	{
	public:
		virtual void Draw() override;
	private:
		RenderingPanel m_RenderingPanel;
	};
}