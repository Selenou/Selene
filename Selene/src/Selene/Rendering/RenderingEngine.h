#pragma once

#include "RenderingAPI.h"
#include "RenderingPipeline.h"
#include "Shader.h"
#include "OrthographicCamera.h"

namespace Selene
{
	class RenderingEngine
	{
	public:
		static void Init();
		static void Clear();
		static void SetViewport(uint32_t width, uint32_t height);
		static void PrepareNewFrame(OrthographicCamera& camera);
		static void Submit(std::shared_ptr<RenderingPipeline> pipeline, std::shared_ptr<Shader> shader);
		static RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }
		static RenderingAPI::Info GetAPIInfo() { return RenderingAPI::GetInfo(); }
	private:
		static std::unique_ptr<RenderingAPI> s_RenderingAPI;
		static glm::mat4 s_ViewProjectionMatrix;
	};
}