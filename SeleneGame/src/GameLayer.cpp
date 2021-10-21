#include "GameLayer.h"

GameLayer::GameLayer() : Layer("Game")
{
	auto& window = Selene::Game::GetInstance().GetWindow();

	m_Camera = std::make_unique<Selene::Camera>();
	m_Camera->SetOrthographic(360); // 640 x 360
	m_Camera->SetPosition({ 320.0f, 180.0f, 0.0f });
	m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());

// 	Selene::Actor cadence = Selene::Game::GetInstance().GetActiveScene()->CreateActor("CadenceBackgroundMusic");
// 	auto& sourceComponent = cadence.AddComponent<Selene::AudioSourceComponent>(Selene::AudioEngine::CreateAudioSource("assets/sounds/fairy.wav"));
// 	sourceComponent.Source->SetIsLooping(true);
// 	sourceComponent.Source->Play();

	m_Tilemap = std::make_unique<Tilemap>();
	m_Tilemap->ParseMap("assets/maps/map.json");
}

void GameLayer::Update(Selene::Timestep ts)
{
	m_Camera->Update(ts);
}

void GameLayer::Render()
{
	Selene::RenderingEngine::BeginFrame(*m_Camera);
	{

		// Player will be a sprite

// 		auto spriteView = Selene::Game::GetInstance().GetActiveScene()->GetRegistry().view<Selene::TransformComponent, Selene::SpriteRendererComponent>();
// 		for (auto entity : spriteView)
// 		{
// 			Selene::RenderingEngine::SubmitSprite(spriteView.get<Selene::TransformComponent>(entity).GetTransform(), spriteView.get<Selene::SpriteRendererComponent>(entity).Sprite);
// 		}

		Selene::RenderingEngine::SubmitBatch(m_Tilemap->m_Pipeline, m_Tilemap->m_Material, m_Tilemap->m_Ebo->GetCount(), m_Tilemap->m_Vbo->GetCount());
	}
	Selene::RenderingEngine::EndFrame();
}

void GameLayer::OnEvent(Selene::Event& event)
{
	Selene::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Selene::FramebufferResizeEvent>([=](Selene::FramebufferResizeEvent& e)
	{
		m_Camera->SetViewportSize(e.GetWidth(), e.GetHeight());
		return false;
	});
}