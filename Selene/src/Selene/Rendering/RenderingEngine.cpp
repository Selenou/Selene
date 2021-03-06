#include "slnpch.h"
#include "RenderingEngine.h"

namespace Selene
{
	void RenderingEngine::Init()
	{
		SLN_INFO("Initializing Rendering Engine");

		s_RenderingEngineData.RenderingAPI = RenderingAPI::Create();
		s_RenderingEngineData.RenderingAPI->Init();
		s_RenderingEngineData.RenderingAPI->SetClearColor({ 1.0f, 1.0f, 0.5f, 1.0f });
		s_RenderingEngineData.RenderingStats = {};

		s_RenderingEngineData.ShaderLibrary = std::make_unique<ShaderLibrary>();
	}

	void RenderingEngine::Clear()
	{
		s_RenderingEngineData.RenderingAPI->Clear();
	}

	void RenderingEngine::SetViewport(uint32_t width, uint32_t height)
	{
		s_RenderingEngineData.RenderingAPI->SetViewport(0, 0, width, height);
	}

	void RenderingEngine::BeginFrame(Camera& camera)
	{
		s_RenderingEngineData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		ResetStats();
	}

	void RenderingEngine::EndFrame() 
	{ 
		s_RenderingEngineData.RenderingStats.Ts = Game::GetInstance().GetTimestep();
	}

	void RenderingEngine::Submit(std::shared_ptr<Pipeline> pipeline, uint32_t count, uint32_t vboCountTmp)
	{
		pipeline->Bind();
		s_RenderingEngineData.RenderingAPI->DrawIndexed(count);

		s_RenderingEngineData.RenderingStats.DrawCalls++;
		s_RenderingEngineData.RenderingStats.TotalVertexCount += vboCountTmp;
		s_RenderingEngineData.RenderingStats.TotalIndexCount += count;
	}

	void RenderingEngine::SubmitMesh(std::shared_ptr<Mesh> mesh)
	{
		mesh->m_Pipeline->Bind();

		for (Submesh& submesh : mesh->m_Submeshes)
		{
			auto& material = mesh->m_Materials[submesh.MaterialIndex];			
			auto& shader = material->GetShader();

			material->Bind();
			shader->SetUniform("u_ViewProjection", s_RenderingEngineData.ViewProjectionMatrix);
			shader->SetUniform("u_Model", mesh->m_Transform);

			s_RenderingEngineData.RenderingAPI->DrawIndexedBaseVertex(submesh.IndexCount, submesh.BaseVertex);

			s_RenderingEngineData.RenderingStats.DrawCalls++;
		}

		s_RenderingEngineData.RenderingStats.TotalVertexCount += mesh->m_Vbo->GetCount();
		s_RenderingEngineData.RenderingStats.TotalIndexCount += mesh->m_Ebo->GetCount();
	}

	void RenderingEngine::SubmitInstanced(uint32_t indiceCount, uint32_t instanceCount)
	{
		s_RenderingEngineData.RenderingAPI->DrawInstanced(indiceCount, instanceCount);
	}

	void RenderingEngine::ResetStats()
	{
		memset(&s_RenderingEngineData.RenderingStats, 0, sizeof(RenderingStats));
	}

	ShaderLibrary* RenderingEngine::GetShaderLibrary() 
	{ 
		return s_RenderingEngineData.ShaderLibrary.get();
	}

	RenderingStats RenderingEngine::GetStats()
	{ 
		return s_RenderingEngineData.RenderingStats;
	}
}