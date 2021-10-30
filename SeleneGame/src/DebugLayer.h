#pragma once

#include "Selene.h"
#include "DebugUI/Panel.h"

class DebugLayer : public Selene::Layer
{
	public:
		DebugLayer();
	protected:
		void RenderUI() override;
	private :
		std::vector<std::unique_ptr<Panel>> m_Panels;
};