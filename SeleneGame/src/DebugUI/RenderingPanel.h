#pragma once

#include "Panel.h"

class RenderingPanel : public Panel
{
	public:
		virtual void Draw() override;
	private:
		int m_AverageFps = 0;
		int m_FrameCounter = 0;
		float m_FrametimeSum = 0.0f;
};