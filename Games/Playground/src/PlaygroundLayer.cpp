#include "PlaygroundLayer.h"

namespace Playground
{
	PlaygroundLayer::PlaygroundLayer()
		: Layer("Playground")
	{
		auto& window = Selene::Game::GetInstance().GetWindow();

		m_Camera = std::make_unique<Selene::Camera>();
		m_Camera->SetOrthographic(2.0f);
		m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());


		m_Source = Selene::AudioEngine::CreateAudioSource("assets/sounds/fairy.wav");
		m_Source->SetIsLooping(true);
		m_Source->Play();
	}

	void PlaygroundLayer::Update(Selene::Timestep ts)
	{
		m_Camera->Update(ts);
	}

	void PlaygroundLayer::Render()
	{
		Selene::RenderingEngine::BeginFrame(*m_Camera);
		{
		
		}
		Selene::RenderingEngine::EndFrame();
	}

	void PlaygroundLayer::OnEvent(Selene::Event& event)
	{
		Selene::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Selene::FramebufferResizeEvent>([=](Selene::FramebufferResizeEvent& e)
		{
			m_Camera->SetViewportSize(e.GetWidth(), e.GetHeight());
			return false;
		});
	}
}