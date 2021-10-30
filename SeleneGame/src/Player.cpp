#include "Player.h"

Player::Player()
{
	Selene::Actor player = Selene::Game::GetInstance().GetActiveScene()->CreateActor("Player");

	player.AddComponent<Selene::SpriteRendererComponent>(std::make_shared<Selene::Sprite>("player.png"));
	player.GetComponent<Selene::TransformComponent>().Position = { 320.0f, -180.0f, 0.0f };

	m_PlayerId = player.GetActorID();

	// AABB
	auto&& aabb = player.AddComponent<Selene::AABBColliderComponent>();
	aabb.Size = { 24.0f, 32.0f };
}

void Player::Update(Selene::Timestep ts)
{
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

	Selene::Actor playerActor{ m_PlayerId, Selene::Game::GetInstance().GetActiveScene() };
	auto&& playerTransform = playerActor.GetComponent<Selene::TransformComponent>();

	playerTransform.Position =
	{ 
		playerTransform.Position.x + (ts * speed * m_PlayerDirection.x),
		playerTransform.Position.y + (ts * speed * m_PlayerDirection.y),
		0.0f 
	};
}
