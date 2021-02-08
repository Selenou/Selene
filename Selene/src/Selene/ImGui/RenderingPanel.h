#pragma once

namespace Selene
{
	class RenderingPanel
	{
	public:
		void DrawPanel();
	private:
		int m_AverageFps = 0;
		int m_FrameCounter = 0;
		float m_FrametimeSum = 0.0f;
	};
}