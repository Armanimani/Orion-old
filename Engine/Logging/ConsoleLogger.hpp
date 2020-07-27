#pragma once

#include <string_view>

#include "Engine/Logging/LoggingLevel.hpp"
#include "Engine/Logging/IConsoleLoggerAdapter.hpp"

namespace orion
{
	class ORION_API ConsoleLogger
	{
	public:
		ConsoleLogger() = delete;

		ConsoleLogger(const ConsoleLogger& other) = delete;
		ConsoleLogger(ConsoleLogger&& other) noexcept = delete;
		ConsoleLogger& operator=(const ConsoleLogger& other) = delete;
		ConsoleLogger& operator=(ConsoleLogger&& other) noexcept = delete;
		~ConsoleLogger() = delete;

		static void enableLoggingLevel(LoggingLevel level) noexcept;
		static void disableLoggingLevel(LoggingLevel level) noexcept;

		[[nodiscard]] static bool isLoggingLevelEnabled(LoggingLevel level) noexcept;

		static void logCritical(std::string_view channel, std::string_view log_message) noexcept;
		static void logWarning(std::string_view channel, std::string_view log_message) noexcept;
		static void logInformation(std::string_view channel, std::string_view log_message) noexcept;
		static void logDebug(std::string_view channel, std::string_view log_message) noexcept;
	private:
		inline static UInt8 s_logging_level {};

		static IConsoleLoggerAdapter* getAdapter();
	};
}
