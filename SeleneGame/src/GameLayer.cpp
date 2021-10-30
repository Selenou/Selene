#include "GameLayer.h"

// TODO :
// Debug draw of box2d => goal = being able to see the player collision
// auto generate collision shape with tiled, use dedicated layer for that => goal = we should be able to walk on a map
// tileson in engine ?
// camera class somehow + lerp inside
// Gamepad support

GameLayer::GameLayer() : Layer("Game")
{
	auto&& window = Selene::Game::GetInstance().GetWindow();

	// Camera
	m_Camera = std::make_unique<Selene::Camera>();
	m_Camera->SetOrthographic(s_ScreenHeight); // 640 x 360
	m_Camera->SetPosition({ s_ScreenHalfWidth, -s_ScreenHalfHeight, 0.0f });
	m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());

	// TileSystem
	m_World = std::make_unique<World>("World_01.world");

	// Player
	m_Player = std::make_unique<Player>();

	Selene::Game::GetInstance().GetActiveScene()->InitPhysicsWorld2D();
}

void GameLayer::Update(Selene::Timestep ts)
{
	Selene::Game::GetInstance().GetActiveScene()->UpdatePhysicsWorld2D(ts);

	m_Player->Update(ts);

	if (m_World->IsPlayerLeavingMap(m_Player->GetPosition()))
	{
		m_World->LoadNextMap(m_Player->GetPosition()/*, m_Player->GetDirection()*/);

		// Replace Camera if a new map is loaded
		auto&& newMapBounds = m_World->GetCurrentMapBounds();

		if (m_World->GetCurrentMapBounds().Top - m_World->GetCurrentMapBounds().Bottom <= m_Camera->GetOrthographicSize()
			&& m_World->GetCurrentMapBounds().Right - m_World->GetCurrentMapBounds().Left <= m_Camera->GetOrthographicSize() * m_Camera->GetAspectRatio())
		{
			m_Camera->SetPosition({
				(newMapBounds.Left + newMapBounds.Right) * .5f,
				(newMapBounds.Top + newMapBounds.Bottom) * .5f,
				0.0f
			});
		}
	}

	// If the map is bigger a full screen one
	if (m_World->GetCurrentMapBounds().Top - m_World->GetCurrentMapBounds().Bottom > m_Camera->GetOrthographicSize()
		|| m_World->GetCurrentMapBounds().Right - m_World->GetCurrentMapBounds().Left > m_Camera->GetOrthographicSize() * m_Camera->GetAspectRatio())
	{
		glm::vec3 from = m_Camera->GetPosition();
		glm::vec3 target = m_Player->GetPosition();
		
		m_Camera->SetPosition({
			std::clamp(from.x + (target.x - from.x) * (1.0f - std::pow(0.01f, ts)), (float)(m_World->GetCurrentMapBounds().Left + s_ScreenHalfWidth), (float)(m_World->GetCurrentMapBounds().Right - s_ScreenHalfWidth)),
			std::clamp(from.y + (target.y - from.y) * (1.0f - std::pow(0.01f, ts)), (float)(m_World->GetCurrentMapBounds().Bottom + s_ScreenHalfHeight), (float)(m_World->GetCurrentMapBounds().Top - s_ScreenHalfHeight)),
			0.0f
		});
	}
}

void GameLayer::Render()
{
	Selene::RenderingEngine::BeginFrame(*m_Camera);
	{
		//Render Tilemap
		Selene::RenderingEngine::SubmitBatch(m_World->GetCurrentMap()->m_Pipeline, 
			m_World->GetCurrentMap()->m_Material, 
			m_World->GetCurrentMap()->m_Ebo->GetCount(), 
			m_World->GetCurrentMap()->m_Vbo->GetCount()
		);

		// Render all sprites
		auto spriteView = Selene::Game::GetInstance().GetActiveScene()->GetRegistry().view<Selene::TransformComponent, Selene::SpriteRendererComponent>();
		for (auto entity : spriteView)
		{
			Selene::RenderingEngine::SubmitSprite(spriteView.get<Selene::TransformComponent>(entity).GetTransform(), spriteView.get<Selene::SpriteRendererComponent>(entity).Sprite);
		}
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