#pragma once

#include <string>
#include <spdlog/spdlog.h>

namespace Comrade
{
	class Logger
	{
	public:
		static void Init(const std::string& name = "ComradeAppLogger");
		inline static std::shared_ptr<spdlog::logger> GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger> GetLogger() { return s_Logger; }

	private:
		inline static std::shared_ptr<spdlog::logger> s_EngineLogger;
		inline static std::shared_ptr<spdlog::logger> s_Logger;
	};
}

#ifdef COMRADE_ENGINE
	#define COMRADE_LOG_INFO(...)		Comrade::Logger::GetEngineLogger()->info(__VA_ARGS__)
	#define COMRADE_LOG_WARN(...)		Comrade::Logger::GetEngineLogger()->warn(__VA_ARGS__)
	#ifdef COMRADE_DEBUG
		#define COMRADE_LOG_DEBUG(...)	Comrade::Logger::GetEngineLogger()->debug(__VA_ARGS__)
	#else
		#define COMRADE_LOG_DEBUG(...)
	#endif
	#define COMRADE_LOG_ERROR(...)		Comrade::Logger::GetEngineLogger()->error(__VA_ARGS__)
	#define COMRADE_LOG_CRITICAL(...)	Comrade::Logger::GetEngineLogger()->critical(__VA_ARGS__)
	#define COMRADE_LOG_TRACE(...)		Comrade::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#else
	#define COMRADE_LOG_INFO(...)		Comrade::Logger::GetLogger()->info(__VA_ARGS__)
	#define COMRADE_LOG_WARN(...)		Comrade::Logger::GetLogger()->warn(__VA_ARGS__)
#ifdef COMRADE_DEBUG
	#define COMRADE_LOG_DEBUG(...)		Comrade::Logger::GetLogger()->debug(__VA_ARGS__)
#else
	#define COMRADE_LOG_DEBUG(...)
#endif
	#define COMRADE_LOG_ERROR(...)		Comrade::Logger::GetLogger()->error(__VA_ARGS__)
	#define COMRADE_LOG_CRITICAL(...)	Comrade::Logger::GetLogger()->critical(__VA_ARGS__)
	#define COMRADE_LOG_TRACE(...)		Comrade::Logger::GetLogger()->trace(__VA_ARGS__)
#endif
