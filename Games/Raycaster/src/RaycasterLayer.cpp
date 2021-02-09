#include "RaycasterLayer.h"

namespace Raycaster
{
	RaycasterLayer::RaycasterLayer()
		: Layer("Raycaster")
	{
		auto& window = Selene::Game::GetInstance().GetWindow();

		m_Camera = std::make_unique<Selene::Camera>();
		m_Camera->SetOrthographic(10.0f);
		m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());
	}

	void RaycasterLayer::Update(Selene::Timestep ts)
	{
		m_Camera->Update(ts);
	}

	void RaycasterLayer::Render()
	{
		Selene::RenderingEngine::BeginFrame(*m_Camera);
		{

		}
		Selene::RenderingEngine::EndFrame();
	}

	void RaycasterLayer::OnEvent(Selene::Event& event)
	{
		Selene::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Selene::FramebufferResizeEvent>([=](Selene::FramebufferResizeEvent& e)
		{
			m_Camera->SetViewportSize(e.GetWidth(), e.GetHeight());
			return false;
		});
	}
}