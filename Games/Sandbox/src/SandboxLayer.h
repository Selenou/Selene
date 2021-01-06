#pragma once

#include "Selene.h"

class SandboxLayer : public Selene::Layer
{

public:
	SandboxLayer();
public:
	virtual void Update() override;
	virtual void RenderUI() override {}
private:
	std::shared_ptr<Selene::Shader> m_Shader;
	std::shared_ptr<Selene::VertexBuffer> m_Vbo;
	std::shared_ptr<Selene::IndexBuffer> m_Ebo;
	std::shared_ptr<Selene::RenderingPipeline> m_Pipeline;
	Selene::OrthographicCamera m_Camera;
};