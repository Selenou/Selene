#pragma once

#include "Selene.h"

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
		std::shared_ptr<Selene::Scene> m_Scene;

		std::shared_ptr<Selene::Shader> m_SkyboxShader;
		std::shared_ptr<Selene::TextureCubeMap> m_TextureCubeMap;
		std::shared_ptr<Selene::VertexBuffer> m_SkyboxVbo;
		std::shared_ptr<Selene::IndexBuffer> m_SkyboxEbo;
		std::shared_ptr<Selene::Pipeline> m_SkyboxPipeline;
};