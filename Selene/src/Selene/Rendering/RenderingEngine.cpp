#include "slnpch.h"
#include "RenderingEngine.h"

namespace Selene
{
	std::unique_ptr<RenderingAPI> RenderingEngine::s_RenderingAPI = nullptr;
	glm::mat4 RenderingEngine::s_ViewProjectionMatrix = glm::mat4(1.0);
	RenderingStats RenderingEngine::s_RenderingStats;

	void RenderingEngine::Init()
	{
		s_RenderingAPI = RenderingAPI::Create();
		s_RenderingAPI->Init();
		s_RenderingStats = {};
	}

	void RenderingEngine::Clear()
	{
		s_RenderingAPI->Clear();
	}

	void RenderingEngine::SetViewport(uint32_t width, uint32_t height)
	{
		s_RenderingAPI->SetViewport(0, 0, width, height);
	}

	void RenderingEngine::PrepareNewFrame(Camera& camera)
	{
		s_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void RenderingEngine::Submit(std::shared_ptr<RenderingPipeline> pipeline, std::shared_ptr<Shader> shader)
	{
		//pipeline->Bind();
		//shader->Bind();
			//glm::mat4 model = glm::mat4(1.0f);
			//shader->SetUniform("u_Model", model);
			//shader->SetUniform("u_ViewProjection", s_ViewProjectionMatrix);
			s_RenderingAPI->DrawIndexed(pipeline->GetIndexBuffer()->GetCount());
		shader->Unbind();
	}
}