#pragma once

#include <ctime>

namespace Selene 
{
	enum class LogSeverity
	{
		Trace,
		Info,
		Warning,
		Error,
		Critical
	};

	class Logger
	{
	public:
		template <class T>
		static inline decltype(auto) FormatArg(T const& t) { return t; }

		static inline const char* FormatArg(std::string const& t) { return t.c_str(); }

		template <typename ... Args>
		static inline void Log(LogSeverity severity, const char* format, Args const& ... args)
		{	
			BuildHeader(severity);
			printf(format, FormatArg(args)...);
			printf("\n");
		}

		static inline void BuildHeader(LogSeverity severity)
		{
			char timeBuffer[11];
			std::time_t currentTime = std::time(nullptr);
			std::strftime(timeBuffer, 11, "[%H:%M:%S]", std::localtime(&currentTime));

			std::string header(timeBuffer);
			header += "[Selene]";
			header += GetSeverityTag(severity);
			header += " ";

			printf(header.c_str());
		}

		static inline char* GetSeverityTag(LogSeverity severity)
		{
			switch (severity)
			{
				case Selene::LogSeverity::Trace:	return "[Trace]";
				case Selene::LogSeverity::Info:		return "[Info]";
				case Selene::LogSeverity::Warning:	return "[Warning]";
				case Selene::LogSeverity::Error:	return "[Error]";
				case Selene::LogSeverity::Critical: return "[Critical]";
				default:							return "[Trace]";
			}
		}
	};
}

#define SLN_TRACE(...)		Selene::Logger::Log(Selene::LogSeverity::Trace, __VA_ARGS__)
#define SLN_INFO(...)		Selene::Logger::Log(Selene::LogSeverity::Info, __VA_ARGS__)
#define SLN_WARN(...)		Selene::Logger::Log(Selene::LogSeverity::Warning, __VA_ARGS__)
#define SLN_ERROR(...)		Selene::Logger::Log(Selene::LogSeverity::Error, __VA_ARGS__)
#define SLN_CRITICAL(...)	Selene::Logger::Log(Selene::LogSeverity::Critical, __VA_ARGS__)