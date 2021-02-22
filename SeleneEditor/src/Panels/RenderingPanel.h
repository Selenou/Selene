#pragma once

#include "EditorPanel.h"

namespace Selene
{
	class RenderingPanel : public EditorPanel
	{
	public:
		virtual void Draw() override;
	private:
		int m_AverageFps = 0;
		int m_FrameCounter = 0;
		float m_FrametimeSum = 0.0f;
	};
}