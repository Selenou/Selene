#include "EditorLayer.h"

#include "Panels/RenderingPanel.h"

namespace Selene
{
	EditorLayer::EditorLayer()
		: Layer("Editor")
	{
		auto& window = Game::GetInstance().GetWindow();

		m_Camera = std::make_unique<Camera>();
		m_Camera->SetOrthographic(2.0f);
		m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());

		m_Panels.emplace_back(std::make_unique<RenderingPanel>());

		m_Scene = std::make_shared<Scene>();

		Actor cadence = m_Scene->CreateActor("CadenceBackgroundMusic");
		auto& sourceComponent = cadence.AddComponent<AudioSourceComponent>(*(AudioEngine::CreateAudioSource("assets/sounds/fairy.wav")));
		sourceComponent.Source.SetIsLooping(true);
		sourceComponent.Source.Play();
	}

	void EditorLayer::Update(Timestep ts)
	{
		m_Camera->Update(ts);
	}

	void EditorLayer::Render()
	{
		RenderingEngine::BeginFrame(*m_Camera);
		{
		
		}
		RenderingEngine::EndFrame();
	}

	void EditorLayer::RenderUI()
	{
		for (auto& panel : m_Panels)
		{
			panel->Draw();
		}
	}

	void EditorLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<FramebufferResizeEvent>([=](FramebufferResizeEvent& e)
		{
			m_Camera->SetViewportSize(e.GetWidth(), e.GetHeight());
			return false;
		});
	}
}