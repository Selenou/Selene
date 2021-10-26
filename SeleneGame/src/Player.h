#pragma once

#include "Selene.h"

class Player
{
public:
	Player();
public:
	void Update(Selene::Timestep ts);
	inline const glm::vec3& GetPosition() const { return m_PlayerTransform->Position; }
private:
	entt::entity m_PlayerId = entt::null;
	Selene::TransformComponent* m_PlayerTransform;
	glm::vec2 m_PlayerDirection = { 0.0f, 0.0f };
};