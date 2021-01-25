#include "slnpch.h"
#include "RenderingEngine.h"

namespace Selene
{
	void RenderingEngine::Init()
	{
		s_RenderingEngineData.m_RenderingAPI = RenderingAPI::Create();
		s_RenderingEngineData.m_RenderingAPI->Init();
		s_RenderingEngineData.m_RenderingStats = {};

		s_RenderingEngineData.m_ShaderLibrary = std::make_unique<ShaderLibrary>();
		s_RenderingEngineData.m_ShaderLibrary->Load("unlit/unlitTexture", "unlit/unlitTexture.vert", "unlit/unlitTexture.frag");
		s_RenderingEngineData.m_ShaderLibrary->Load("skybox", "skybox.vert", "skybox.frag");
	}

	void RenderingEngine::Clear()
	{
		s_RenderingEngineData.m_RenderingAPI->Clear();
	}

	void RenderingEngine::SetViewport(uint32_t width, uint32_t height)
	{
		s_RenderingEngineData.m_RenderingAPI->SetViewport(0, 0, width, height);
	}

	void RenderingEngine::BeginFrame(Camera& camera)
	{
		s_RenderingEngineData.m_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		ResetStats();
	}

	void RenderingEngine::EndFrame() 
	{ 
		s_RenderingEngineData.m_RenderingStats.Ts = Game::GetInstance().GetTimestep();
	}

	void RenderingEngine::Submit(std::shared_ptr<Pipeline> pipeline, uint32_t count, uint32_t vboCountTmp)
	{
		pipeline->Bind();
		s_RenderingEngineData.m_RenderingAPI->DrawIndexed(count);

		s_RenderingEngineData.m_RenderingStats.DrawCalls++;
		s_RenderingEngineData.m_RenderingStats.TotalVertexCount += vboCountTmp;
		s_RenderingEngineData.m_RenderingStats.TotalIndexCount += count;
	}

	void RenderingEngine::SubmitMesh(std::shared_ptr<Mesh> mesh)
	{
		mesh->m_Pipeline->Bind();

		for (Submesh& submesh : mesh->m_Submeshes)
		{
			auto& material = mesh->m_Materials[submesh.MaterialIndex];
			auto& shader = material->GetShader();

			material->Bind();
			shader->SetUniform("u_ViewProjection", s_RenderingEngineData.m_ViewProjectionMatrix);
			shader->SetUniform("u_Model", mesh->m_Transform);

			s_RenderingEngineData.m_RenderingAPI->DrawIndexedBaseVertex(submesh.IndexCount, submesh.BaseVertex);

			s_RenderingEngineData.m_RenderingStats.DrawCalls++;
		}

		s_RenderingEngineData.m_RenderingStats.TotalVertexCount += mesh->m_Vbo->GetCount();
		s_RenderingEngineData.m_RenderingStats.TotalIndexCount += mesh->m_Ebo->GetCount();
	}

	void RenderingEngine::ResetStats()
	{
		memset(&s_RenderingEngineData.m_RenderingStats, 0, sizeof(RenderingStats));
	}

	ShaderLibrary* RenderingEngine::GetShaderLibrary() 
	{ 
		return s_RenderingEngineData.m_ShaderLibrary.get();
	}

	RenderingStats RenderingEngine::GetStats()
	{ 
		return s_RenderingEngineData.m_RenderingStats;
	}
}