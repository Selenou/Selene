#pragma once

#include "Selene.h"

namespace Raycaster
{
	class RaycasterLayer : public Selene::Layer
	{
	public:
		RaycasterLayer();
	public:
		virtual void Update(Selene::Timestep ts) override;
		virtual void Render() override;
		virtual void OnEvent(Selene::Event& event) override;
	private :
		std::unique_ptr<Selene::Camera> m_Camera;
	};
}