#pragma once

#include "ImGuiHandler.h"
#include "SingletonTemplate.h"
#include "Library/Aixlog.hpp" // NOLINT(clang-diagnostic-microsoft-include)
#include "Library/imgui/imgui.h"

#define LOG_INFO(message) LOG(INFO) << (message) << std::endl
#define LOG_WARNING(message) LOG(WARNING) << (message) << std::endl
#define LOG_ERROR(message) LOG(5) << (message) << std::endl

namespace Griddy
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
				std::make_shared<SinkCallback>(Severity::trace, 
				[](const Metadata& metadata, const std::string& internalMessage)
				{
					// TODO: Fix this its way to hacky for me to release
					std::ostringstream ss;
					const auto log = std::make_shared<SinkCout>(Severity::trace, "%H:%M.%S [#severity] [#file | Function: #function | Line: #line] #message");
					log->log(ss, metadata, internalMessage);
					
					ImGuiHandler::Instance()->addLog(ss.str());
				}
			)
			});

			LOG_INFO("Logger initialized");
		}
	};
}
