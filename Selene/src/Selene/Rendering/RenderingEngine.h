#pragma once

#include "RenderingAPI.h"
#include "Pipeline.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Selene/Core/Game.h"
#include "Selene/Core/Time.h"

namespace Selene
{
	struct RenderingStats
	{
		Timestep Ts;
		uint32_t DrawCalls = 0;
		uint32_t TotalVertexCount = 0;
		uint32_t TotalIndexCount = 0;
	};

	class RenderingEngine
	{
	public:
		static void Init();
		static void Clear();
		static void SetViewport(uint32_t width, uint32_t height);
		static void BeginFrame(Camera& camera);
		static void EndFrame();
		static void Submit(std::shared_ptr<Pipeline> pipeline, uint32_t count, uint32_t vboCountTmp); // remove vboCountTmp 
		static void SubmitMesh(std::shared_ptr<Mesh> mesh);
	public:
		static inline RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }
		static inline RenderingAPI::Info GetAPIInfo() { return RenderingAPI::GetInfo(); }
		static inline RenderingStats GetStats() { return s_RenderingStats; }
	private:
		static void ResetStats();
	private:
		static std::unique_ptr<RenderingAPI> s_RenderingAPI;
		static glm::mat4 s_ViewProjectionMatrix;
		static RenderingStats s_RenderingStats;
	};
}