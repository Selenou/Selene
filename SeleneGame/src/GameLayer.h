#pragma once

#include "Selene.h"

#include "TileSystem/World.h"

class GameLayer : public Selene::Layer
{
	public:
		GameLayer();
	protected:
		void Update(Selene::Timestep ts) override;
		void Render() override;
		void OnEvent(Selene::Event& event) override;
	private:
		std::unique_ptr<Selene::Camera> m_Camera;
		std::unique_ptr<World> m_World;

		entt::entity m_PlayerId = entt::null;
		glm::vec2 m_PlayerDirection = { 0.0f, 0.0f };
};