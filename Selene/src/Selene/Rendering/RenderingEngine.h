#pragma once

#include "RenderingAPI.h"
#include "RenderingPipeline.h"
#include "Shader.h"
#include "Camera.h"
#include "Selene/Core/Game.h"
#include "Selene/Core/Time.h"

namespace Selene
{
	struct RenderingStats
	{
		Timestep ts;
	};

	class RenderingEngine
	{
	public:
		static void Init();
		static void Clear();
		static void SetViewport(uint32_t width, uint32_t height);
		static void PrepareNewFrame(Camera& camera);
		static void Submit(std::shared_ptr<RenderingPipeline> pipeline, std::shared_ptr<Shader> shader);
		static inline RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }
		static inline RenderingAPI::Info GetAPIInfo() { return RenderingAPI::GetInfo(); }
		static inline RenderingStats GetStats()
		{ 
			s_RenderingStats.ts = Game::GetInstance().GetTimestep();
			return s_RenderingStats; 
		}
	private:
		static std::unique_ptr<RenderingAPI> s_RenderingAPI;
		static glm::mat4 s_ViewProjectionMatrix;
		static RenderingStats s_RenderingStats;
	};
}