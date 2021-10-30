#pragma once

#include "Selene.h"

class Player
{
public:
	Player();
public:
	void Update(Selene::Timestep ts);
	inline const glm::vec3& GetPosition() const 
	{ 
		Selene::Actor playerActor{ m_PlayerId, Selene::Game::GetInstance().GetActiveScene() };
		return playerActor.GetComponent<Selene::TransformComponent>().Position;
	}

	inline const glm::vec2& GetDirection() const { return m_PlayerDirection; }
private:
	entt::entity m_PlayerId = entt::null;
	glm::vec2 m_PlayerDirection = { 0.0f, 0.0f };
};