#include "GameLayer.h"

// TODO :
// // tileson and box2d in engine ?
// Gamepad support
// camera class somehow
// proper camera lerping system

GameLayer::GameLayer() : Layer("Game")
{
	auto&& window = Selene::Game::GetInstance().GetWindow();

	// Camera
	m_Camera = std::make_unique<Selene::Camera>();
	m_Camera->SetOrthographic(360); // 640 x 360
	m_Camera->SetPosition({ 320.0f, -180.0f, 0.0f });
	m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());

	// TileSystem
	m_World = std::make_unique<World>("World_01.world");

	// Player
	m_Player = std::make_unique<Player>();
}

void GameLayer::Update(Selene::Timestep ts)
{
	m_Player->Update(ts);

	if (m_World->IsPlayerLeavingMap(m_Player->GetPosition()))
	{
		m_World->LoadNextMap(m_Player->GetPosition());

		// Replace Camera if a new map is loaded
		auto&& newMapBorder = m_World->GetCurrentMapBorder();
		m_Camera->SetPosition({ 
			(newMapBorder.Left + newMapBorder.Right) * .5f, 
			(newMapBorder.Top + newMapBorder.Bottom) * .5f, 
			0.0f 
		});
	}

	// Lerp test if the camera is too far away from the player
	// TODO : clamp camera position to map border
	if (m_World->GetCurrentMapBorder().Top - m_World->GetCurrentMapBorder().Bottom > m_Camera->GetOrthographicSize() &&
		glm::abs(m_Camera->GetPosition().y - m_Player->GetPosition().y) > m_Camera->GetOrthographicSize() / 5)
	{
		auto&& newMapBorder = m_World->GetCurrentMapBorder();
		m_Camera->SetPosition({
			m_Camera->GetPosition().x,
			m_Player->GetPosition().y,
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


// 	float lerp(float x, float y, float t)
// 	{
// 		return x * (1.f - t) + y * t;
// 	}
	// Test lerp, move lerp fct somewhere
	//auto&& newMapBorder = m_World->GetCurrentMapBorder();
	//float h = (newMapBorder[0] + newMapBorder[1]) * .5f;
	//float v = (newMapBorder[2] + newMapBorder[3]) * .5f;
	//acc-lerpAcc should be just a percentage from 0 to 1, need to accumulate ts and percentage = currentLerpTime / lerpTime;
	//m_Camera->SetPosition({ h, lerp(lerpToto, v, acc-lerpAcc), 0.0f });
	//SLN_TRACE("%f, %f", lerpToto, v);
	//SLN_WARN("%f, %f", m_Camera->GetPosition().x, m_Camera->GetPosition().y);