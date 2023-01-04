#include "Engine.h"
#include "Util/aixlog.hpp"

#define LOG_INFO(message) LOG(INFO) << message << std::endl
#define LOG_WARNING(message) LOG(WARNING) << message << std::endl
#define LOG_ERROR(message) LOG(5) << message << std::endl

namespace Disunity
{
	void Engine::m_SetupLogger()
	{
		using namespace AixLog;

		// Create a logger
		AixLog::Log::init(
		{
			std::make_shared<AixLog::SinkCout>(Severity::trace, "%H:%M.%S [#severity] [#file | Function: #function | Line: #line] #message"),
			std::make_unique<AixLog::SinkFile>(Severity::trace, "latest.log", "%H:%M.%S [#severity] [#file | Function: #function | Line: #line] #message"),
			std::make_shared<AixLog::SinkNative>("aixlog", AixLog::Severity::trace),
		});

		LOG_INFO("Logger initialized");
		LOG_WARNING("Logger initialized");
		LOG_ERROR("Logger initialized");
	}

	bool Engine::m_Init()
	{
		// init

		m_SetupLogger();
		return true;
	}

	void Engine::m_Update()
	{
		// update
	}

	void Engine::m_Render()
	{
		// render
	}

	void Engine::m_Cleanup()
	{
		// cleanup
	}

	void Engine::Run()
	{
		if (!m_Init())
		{
			// TODO: LOG HERE/CRASH OUT

			// TODO: Should cleanup actually be here?
			m_Cleanup();
			return;
		}

		m_Initialized = true;
		m_Running = true;

		while (m_Running)
		{
			m_Update();
			m_Render();
		}

		m_Cleanup();
	}
}