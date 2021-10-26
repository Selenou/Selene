#include "Player.h"

Player::Player()
{
	Selene::Actor player = Selene::Game::GetInstance().GetActiveScene()->CreateActor("Player");

	Selene::SpriteRendererComponent spriteComponent = player.AddComponent<Selene::SpriteRendererComponent>(std::make_shared<Selene::Sprite>("player.png"));

	m_PlayerTransform = &(player.GetComponent<Selene::TransformComponent>());
	m_PlayerTransform->Position = { 320.0f, -180.0f, 0.0f };

	m_PlayerId = player.GetActorID();
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

	m_PlayerTransform->Position = 
	{ 
		m_PlayerTransform->Position.x + (ts * speed * m_PlayerDirection.x), 
		m_PlayerTransform->Position.y + (ts * speed * m_PlayerDirection.y), 
		0.0f 
	};
}
