#pragma once

#include "Logger.h"

#define SLN_ASSERT(x, ...)		if(!x) { SLN_CRITICAL(__VA_ARGS__); __debugbreak(); } 
#define SLN_BIND_EVENT(evt)		[this](auto&&... args) { return evt(std::forward<decltype(args)>(args)...); } // Variadic Generic Lambda, C++14 (Lambda is faster than bind)

#define SLN_TRACE(...)			Selene::Logger::Log(Selene::LogSeverity::Trace, __VA_ARGS__)
#define SLN_INFO(...)			Selene::Logger::Log(Selene::LogSeverity::Info, __VA_ARGS__)
#define SLN_WARN(...)			Selene::Logger::Log(Selene::LogSeverity::Warning, __VA_ARGS__)
#define SLN_ERROR(...)			Selene::Logger::Log(Selene::LogSeverity::Error, __VA_ARGS__)
#define SLN_CRITICAL(...)		Selene::Logger::Log(Selene::LogSeverity::Critical, __VA_ARGS__)