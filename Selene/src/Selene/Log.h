#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Selene {

	class SELENE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetGameLogger() { return s_GameLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_GameLogger;
	};

}

// Engine
#define SLN_ENGINE_TRACE(...) ::Selene::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define SLN_ENGINE_INFO(...) ::Selene::Log::GetEngineLogger()->info(__VA_ARGS__)
#define SLN_ENGINE_WARN(...) ::Selene::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define SLN_ENGINE_ERROR(...) ::Selene::Log::GetEngineLogger()->error(__VA_ARGS__)
#define SLN_ENGINE_FATAL(...) ::Selene::Log::GetEngineLogger()->fatal(__VA_ARGS__)

// Game
#define SLN_TRACE(...) ::Selene::Log::GetGameLogger()->trace(__VA_ARGS__)
#define SLN_INFO(...) ::Selene::Log::GetGameLogger()->info(__VA_ARGS__)
#define SLN_WARN(...) ::Selene::Log::GetGameLogger()->warn(__VA_ARGS__)
#define SLN_ERROR(...) ::Selene::Log::GetGameLogger()->error(__VA_ARGS__)
#define SLN_FATAL(...) ::Selene::Log::GetGameLogger()->fatal(__VA_ARGS__)