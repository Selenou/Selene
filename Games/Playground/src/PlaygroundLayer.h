#pragma once

#include "Selene.h"

namespace Playground
{
	class PlaygroundLayer : public Selene::Layer
	{
	public:
		PlaygroundLayer();
		~PlaygroundLayer();
	public:
		virtual void Update(Selene::Timestep ts) override;
		virtual void Render() override;
		virtual void OnEvent(Selene::Event& event) override;
	private :
		std::unique_ptr<Selene::Camera> m_Camera;
		Selene::AudioSource* source;
	};
}