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

	void RenderingEngine::Submit(std::shared_ptr<Pipeline> pipeline, uint32_t count)
	{
		pipeline->Bind();
		s_RenderingAPI->DrawIndexed(count);
	}

	void RenderingEngine::SubmitMesh(std::shared_ptr<Mesh> mesh)
	{
		mesh->m_Pipeline->Bind();

		mesh->m_Shader->Bind();
		mesh->m_Shader->SetUniform("u_ViewProjection", s_ViewProjectionMatrix);
		mesh->m_Shader->SetUniform("u_Model", mesh->m_Transform);

		mesh->m_Texture->Bind();

		for (Submesh& submesh : mesh->m_Submeshes)
		{
			s_RenderingAPI->DrawIndexedBaseVertex(submesh.IndexCount, submesh.BaseVertex);
		}
	}
}