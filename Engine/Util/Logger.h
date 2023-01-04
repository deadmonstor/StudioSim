#pragma once

#include "SingletonTemplate.h"
#include "Library/Aixlog.hpp"  // NOLINT(clang-diagnostic-microsoft-include)

#define LOG_INFO(message) LOG(INFO) << (message) << std::endl
#define LOG_WARNING(message) LOG(WARNING) << (message) << std::endl
#define LOG_ERROR(message) LOG(5) << (message) << std::endl

namespace Disunity
{
	class Logger : public SingletonTemplate<Logger>
	{
	public:
		void init() const
		{
			using namespace AixLog;

			Log::init({
				std::make_shared<SinkCout>(Severity::trace,
										   "%H:%M.%S [#severity] [#file | Function: #function | Line: #line] #message"),
				std::make_unique<SinkFile>(Severity::trace, "latest.log",
										   "%H:%M.%S [#severity] [#file | Function: #function | Line: #line] #message"),
				std::make_shared<SinkNative>("aixlog", Severity::trace),
			});

			LOG_INFO("Logger initialized");
		}
	};
}
