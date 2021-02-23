#pragma once

#include "EditorPanel.h"
#include "RenderingPanel.h"

namespace Selene 
{
	class ViewportPanel : public EditorPanel
	{
	public:
		virtual void Draw() override;
	private:
		RenderingPanel m_RenderingPanel;
	};
}