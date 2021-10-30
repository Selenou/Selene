#pragma once

#include "RenderingAPI.h"
#include "Pipeline.h"
#include "Mesh.h"
#include "Sprite.h"
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

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	struct RenderingEngineData
	{
		RenderingStats RenderingStats;
		std::unique_ptr<RenderingAPI> RenderingAPI = nullptr;
		std::unique_ptr<ShaderLibrary> ShaderLibrary = nullptr;
		glm::mat4 ViewProjectionMatrix = glm::mat4(1.0);
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class RenderingEngine
	{
	public:
		static void Init();
		static void Clear();
		static void SetViewport(uint32_t width, uint32_t height);
		static void BeginFrame(Camera& camera);
		static void EndFrame();
		static void Submit(std::shared_ptr<Pipeline> pipeline, uint32_t count, uint32_t vboCountTmp); // TODO : remove vboCountTmp 
		static void SubmitMesh(const glm::mat4& transform, std::shared_ptr<Mesh> mesh);
		static void SubmitSprite(const glm::mat4& transform, std::shared_ptr<Sprite> sprite);
		static void SubmitAABBDebug(const glm::mat4& transform, const glm::vec2& size );
		static void SubmitBatch(std::shared_ptr<Pipeline> pipeline, std::shared_ptr<Material> material, uint32_t count, uint32_t vboCountTmp); // TODO : remove vboCountTmp 
		static void SubmitInstanced(uint32_t indiceCount, uint32_t instanceCount);
	public:
		static inline RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }
		static inline RenderingAPI::Info GetAPIInfo() { return RenderingAPI::GetInfo(); }
		static RenderingStats GetStats();
		static ShaderLibrary* GetShaderLibrary();
	private:
		static void ResetStats();
	private:
		static inline RenderingEngineData s_RenderingEngineData; // C++17 : definition + declaration in header with inline for static
	};
}