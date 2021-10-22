#include "GameLayer.h"

GameLayer::GameLayer() : Layer("Game")
{
	auto& window = Selene::Game::GetInstance().GetWindow();

	// Camera
	m_Camera = std::make_unique<Selene::Camera>();
	m_Camera->SetOrthographic(360); // 640 x 360
	m_Camera->SetPosition({ 320.0f, 180.0f, 0.0f });
	m_Camera->SetViewportSize(window.GetWidth(), window.GetHeight());

	// TileSystem
	m_World = std::make_unique<World>("World_01.world");
	//m_Tilemap = std::make_unique<Map>();
	//m_Tilemap->ParseMap("assets/maps/map.json");

	// Player
	Selene::Actor player = Selene::Game::GetInstance().GetActiveScene()->CreateActor("Player");
	Selene::SpriteRendererComponent spriteComponent = player.AddComponent<Selene::SpriteRendererComponent>(std::make_shared<Selene::Sprite>("player.png"));
	player.GetComponent<Selene::TransformComponent>().Position = { 300.0f, 152.0f, 0.0f };
	m_PlayerId = player.GetActorID();
}

void GameLayer::Update(Selene::Timestep ts)
{
	//m_Camera->Update(ts);

	m_PlayerDirection = { 0.0f, 0.0f };

	if (Selene::Input::IsKeyPressed(Selene::Key::D))
		m_PlayerDirection.x = 1.0f;
	else if (Selene::Input::IsKeyPressed(Selene::Key::A))
		m_PlayerDirection.x = -1.0f;

	if (Selene::Input::IsKeyPressed(Selene::Key::W))
		m_PlayerDirection.y = 1.0f;
	else if (Selene::Input::IsKeyPressed(Selene::Key::S))
		m_PlayerDirection.y = -1.0f;

	float speed = 200.0f;

	Selene::Actor player = Selene::Actor(m_PlayerId, Selene::Game::GetInstance().GetActiveScene());
	player.GetComponent<Selene::TransformComponent>().Position = { player.GetComponent<Selene::TransformComponent>().Position.x + (ts * speed * m_PlayerDirection.x), player.GetComponent<Selene::TransformComponent>().Position.y + (ts * speed * m_PlayerDirection.y), 0.0f };
	SLN_TRACE("Player position : {%f,%f}", player.GetComponent<Selene::TransformComponent>().Position.x, player.GetComponent<Selene::TransformComponent>().Position.y);

	m_Camera->SetPosition(player.GetComponent<Selene::TransformComponent>().Position);
	m_World->Update(player);
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