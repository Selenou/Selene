#pragma once

#include "Selene.h"
#include "Player.h"

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
		std::unique_ptr<Player> m_Player;
		std::unique_ptr<World> m_World;
};