#pragma once

#include "EditorUI.h"

namespace Selene
{
	class RenderingPanel : public EditorUI
	{
	public:
		virtual void Draw() override;
	private:
		int m_AverageFps = 0;
		int m_FrameCounter = 0;
		float m_FrametimeSum = 0.0f;
	};
}