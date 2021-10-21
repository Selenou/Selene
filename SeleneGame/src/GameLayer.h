#pragma once

#include "Selene.h"
#include "Tilemap.h"

class GameLayer : public Selene::Layer
{
	public:
		GameLayer();
	protected:
		virtual void Update(Selene::Timestep ts) override;
		virtual void Render() override;
		virtual void OnEvent(Selene::Event& event) override;
	private:
		std::unique_ptr<Selene::Camera> m_Camera;
		std::unique_ptr<Tilemap> m_Tilemap;
};