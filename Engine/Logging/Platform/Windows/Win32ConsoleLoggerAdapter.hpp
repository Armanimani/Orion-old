#pragma once

#include <unordered_map>
#include <string>

#include "Engine/Logging/IConsoleLoggerAdapter.hpp"
#include "Engine/Logging/LoggingLevel.hpp"

namespace orion
{
	class ORION_API Win32ConsoleLoggerAdapter final : public IConsoleLoggerAdapter
	{
	public:
		void logCritical(std::string_view channel, std::string_view log_message) noexcept override;
		void logWarning(std::string_view channel, std::string_view log_message) noexcept override;
		void logInformation(std::string_view channel, std::string_view log_message) noexcept override;
		void logDebug(std::string_view channel, std::string_view log_message) noexcept override;
	private:
		static std::unordered_map<LoggingLevel, UInt8> s_console_color_map;
		static std::unordered_map<LoggingLevel, std::string>  s_severity_token_map;

		void logMessage(std::string_view channel, std::string_view log_message, LoggingLevel level) const noexcept;

		[[nodiscard]] std::string getFormattedTime() const noexcept;
		[[nodiscard]] std::string getFormattedMessage (std::string_view channel, std::string_view log_message, LoggingLevel level) const noexcept;
	};
}
