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
		template <typename T>
		static inline decltype(auto) FormatArg(T const& t) { return t; }

		static inline const char* FormatArg(std::string const& t) { return t.c_str(); }

		template <typename ... Args>
		static inline void Log(LogSeverity severity, const char* format, Args const& ... args)
		{
			// Timestamp
			char timeBuffer[11];
			std::time_t currentTime = std::time(nullptr);
			std::strftime(timeBuffer, 11, "[%H:%M:%S]", std::localtime(&currentTime));

			std::string logStr(timeBuffer);
			logStr += "[Selene]";
			logStr += GetSeverityTag(severity);
			logStr += " ";
			logStr += format;
 
			// Write formatted log in a buffer (with computed size)
			size_t bufferSize = snprintf(nullptr, 0, logStr.c_str(), FormatArg(args) ...) + 1; // Extra space for '\0'
			std::unique_ptr<char[]> buffer(new char[bufferSize]);
			snprintf(buffer.get(), bufferSize, logStr.c_str(), FormatArg(args) ...);

			// Write in console, Color might not work depending on VS settings (see below)
			// https://developercommunity.visualstudio.com/t/console-colors-dont-work-when-automatically-close/599998
			printf("%s%s\n", GetSeverityColor(severity), buffer.get());
			// For Selene Editor
			s_Logs.emplace_back(severity, std::string(buffer.get()));
		}

		static inline char* GetSeverityTag(LogSeverity severity)
		{
			switch (severity)
			{
				case LogSeverity::Trace:	return "[Trace]";
				case LogSeverity::Info:		return "[Info]";
				case LogSeverity::Warning:	return "[Warning]";
				case LogSeverity::Error:	return "[Error]";
				case LogSeverity::Critical: return "[Critical]";
				default:					return "[Trace]";
			}
		}

		static inline char* GetSeverityColor(LogSeverity severity)
		{
			switch (severity)
			{
				case LogSeverity::Trace:	return "\033[0;97m";
				case LogSeverity::Info:		return "\033[0;92m";
				case LogSeverity::Warning:	return "\033[0;93m";
				case LogSeverity::Error:	return "\033[0;91m";
				case LogSeverity::Critical: return "\033[0;101m";
				default:					return "\033[0;97m";
			}
		}

	public:
		static inline void ClearLogs() { s_Logs.clear(); }
		static inline std::vector<std::pair<LogSeverity, std::string>>& GetLogs() { return s_Logs; }
	public:
		static inline std::vector<std::pair<LogSeverity, std::string>> s_Logs;
	};
}