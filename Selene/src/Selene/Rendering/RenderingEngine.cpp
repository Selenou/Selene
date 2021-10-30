#include "slnpch.h"
#include "RenderingEngine.h"

namespace Selene
{
	void RenderingEngine::Init()
	{
		SLN_INFO("Initializing Rendering Engine");

		s_RenderingEngineData.RenderingAPI = RenderingAPI::Create();
		s_RenderingEngineData.RenderingAPI->Init();
		s_RenderingEngineData.RenderingAPI->SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
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

	void RenderingEngine::SubmitMesh(const glm::mat4& transform, std::shared_ptr<Mesh> mesh)
	{
		mesh->m_Pipeline->Bind();

		for (Submesh& submesh : mesh->m_Submeshes)
		{
			auto& material = mesh->m_Materials[submesh.MaterialIndex];			
			auto& shader = material->GetShader();

			material->Bind();
			shader->SetUniform("u_ViewProjection", s_RenderingEngineData.ViewProjectionMatrix);
			shader->SetUniform("u_Model", transform);

			s_RenderingEngineData.RenderingAPI->DrawIndexedBaseVertex(submesh.IndexCount, submesh.BaseVertex);

			s_RenderingEngineData.RenderingStats.DrawCalls++;
		}

		s_RenderingEngineData.RenderingStats.TotalVertexCount += mesh->m_Vbo->GetCount();
		s_RenderingEngineData.RenderingStats.TotalIndexCount += mesh->m_Ebo->GetCount();
	}

	void RenderingEngine::SubmitSprite(const glm::mat4& transform, std::shared_ptr<Sprite> sprite)
	{
		sprite->m_Pipeline->Bind();

		sprite->m_Material->Bind();
		auto& shader = sprite->m_Material->GetShader();

		shader->SetUniform("u_ViewProjection", s_RenderingEngineData.ViewProjectionMatrix);
		shader->SetUniform("u_Model", transform);

		s_RenderingEngineData.RenderingAPI->DrawIndexed(sprite->m_Ebo->GetCount());

		s_RenderingEngineData.RenderingStats.TotalVertexCount += sprite->m_Vbo->GetCount();
		s_RenderingEngineData.RenderingStats.TotalIndexCount += sprite->m_Ebo->GetCount();

		s_RenderingEngineData.RenderingStats.DrawCalls++;
	}

	void RenderingEngine::SubmitAABBDebug(const glm::mat4& transform, const glm::vec2& size)
	{
		auto m_Material = Material::Create(RenderingEngine::GetShaderLibrary()->Get("unlit/aabbDebug"));

		std::vector<float> vertices =
		{
			-0.5f * size.x , -0.5f * size.y,
			0.5f * size.x, -0.5f * size.y,
			0.5f * size.x, 0.5f * size.y,
			-0.5f * size.x, 0.5f * size.y,
		};

		std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };

		auto m_Vbo = VertexBuffer::Create(vertices.data(), (uint32_t)(2 * 4 * sizeof(float)));
		auto m_Ebo = IndexBuffer::Create(indices.data(), (uint32_t)(6 * sizeof(uint32_t)));

		VertexBufferLayout layout = VertexBufferLayout({{ "a_Position", DataType::Float2 }});

		m_Vbo->SetLayout(layout);

		auto m_Pipeline = Pipeline::Create();
		m_Pipeline->BindVertexBuffer(m_Vbo);
		m_Pipeline->BindIndexBuffer(m_Ebo);

		// Actual draw
		m_Pipeline->Bind();
		m_Material->Bind();

		auto& shader = m_Material->GetShader();
		shader->SetUniform("u_ViewProjection", s_RenderingEngineData.ViewProjectionMatrix);
		shader->SetUniform("u_Model", transform);

 		s_RenderingEngineData.RenderingAPI->DrawIndexed(6);

		s_RenderingEngineData.RenderingStats.DrawCalls++;
		s_RenderingEngineData.RenderingStats.TotalVertexCount += 4;
		s_RenderingEngineData.RenderingStats.TotalIndexCount += 6;
	}

	void RenderingEngine::SubmitBatch(std::shared_ptr<Pipeline> pipeline, std::shared_ptr<Material> material, uint32_t count, uint32_t vboCountTmp)
	{
		pipeline->Bind();
		material->Bind();

		auto& shader = material->GetShader();
		shader->SetUniform("u_ViewProjection", s_RenderingEngineData.ViewProjectionMatrix);
		shader->SetUniform("u_Model", glm::mat4(1.0f));

		s_RenderingEngineData.RenderingAPI->DrawIndexed(count);

		s_RenderingEngineData.RenderingStats.DrawCalls++;
		s_RenderingEngineData.RenderingStats.TotalVertexCount += vboCountTmp;
		s_RenderingEngineData.RenderingStats.TotalIndexCount += count;
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