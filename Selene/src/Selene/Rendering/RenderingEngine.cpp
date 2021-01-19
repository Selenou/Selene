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

	void RenderingEngine::BeginFrame(Camera& camera)
	{
		s_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		ResetStats();
	}

	void RenderingEngine::EndFrame() 
	{ 
		s_RenderingStats.Ts = Game::GetInstance().GetTimestep(); 
	}

	void RenderingEngine::Submit(std::shared_ptr<Pipeline> pipeline, uint32_t count, uint32_t vboCountTmp)
	{
		pipeline->Bind();
		s_RenderingAPI->DrawIndexed(count);

		s_RenderingStats.DrawCalls++;
		s_RenderingStats.TotalVertexCount += vboCountTmp;
		s_RenderingStats.TotalIndexCount += count;
	}

	void RenderingEngine::SubmitMesh(std::shared_ptr<Mesh> mesh)
	{
		mesh->m_Pipeline->Bind();

		for (Submesh& submesh : mesh->m_Submeshes)
		{
			auto& material = mesh->m_Materials[submesh.MaterialIndex];
			auto& shader = material->GetShader();

			material->Bind();
			shader->SetUniform("u_ViewProjection", s_ViewProjectionMatrix);
			shader->SetUniform("u_Model", mesh->m_Transform);

			s_RenderingAPI->DrawIndexedBaseVertex(submesh.IndexCount, submesh.BaseVertex);

			s_RenderingStats.DrawCalls++;
		}

		s_RenderingStats.TotalVertexCount += mesh->m_Vbo->GetCount();
		s_RenderingStats.TotalIndexCount += mesh->m_Ebo->GetCount();
	}

	void RenderingEngine::ResetStats()
	{
		memset(&s_RenderingStats, 0, sizeof(RenderingStats));
	}
}