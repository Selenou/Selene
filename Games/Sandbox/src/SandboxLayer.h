#pragma once

#include "Selene.h"

class SandboxLayer : public Selene::Layer
{
public:
	SandboxLayer();
public:
	virtual void Update(Selene::Timestep ts) override;
	virtual void RenderUI() override;
	virtual void OnEvent(Selene::Event& event) override;
private:
	std::shared_ptr<Selene::Mesh> m_Mesh;
	std::shared_ptr<Selene::Mesh> m_MeshTest;

	std::shared_ptr<Selene::Shader> m_SkyboxShader;
	std::shared_ptr<Selene::TextureCubeMap> m_TextureCubeMap;
	std::shared_ptr<Selene::VertexBuffer> m_SkyboxVbo;
	std::shared_ptr<Selene::IndexBuffer> m_SkyboxEbo;
	std::shared_ptr<Selene::Pipeline> m_SkyboxPipeline;

	std::unique_ptr<Selene::Camera> m_Camera;

	bool usePerspective = true;
	bool useWireframeMode = false;
};