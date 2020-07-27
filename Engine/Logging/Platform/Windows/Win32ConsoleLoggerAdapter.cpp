#include "Engine/Logging/Platform/Windows/Win32ConsoleLoggerAdapter.hpp"
#include "Engine/Time/CalenderClock.hpp"

#include <iostream>
#include <Windows.h>

namespace orion
{
	std::unordered_map<LoggingLevel, UInt8> Win32ConsoleLoggerAdapter::s_console_color_map =
	{
		{LoggingLevel::critical, FOREGROUND_RED},
		{LoggingLevel::warning, FOREGROUND_GREEN | FOREGROUND_RED},
		{LoggingLevel::information, FOREGROUND_GREEN | FOREGROUND_BLUE},
		{LoggingLevel::debug, FOREGROUND_GREEN}
	};

	std::unordered_map<LoggingLevel, std::string> Win32ConsoleLoggerAdapter::s_severity_token_map =
	{
		{LoggingLevel::critical, "ERROR"},
		{LoggingLevel::warning, "WARNING"},
		{LoggingLevel::information, "INFORMATION"},
		{LoggingLevel::debug, "DEBUG"}
	};


	void Win32ConsoleLoggerAdapter::logCritical(const std::string_view channel, const std::string_view log_message) noexcept
	{
		logMessage(channel, log_message, LoggingLevel::critical);
	}
	
	void Win32ConsoleLoggerAdapter::logWarning(const std::string_view channel, const std::string_view log_message) noexcept
	{
		logMessage(channel, log_message, LoggingLevel::warning);
	}
	
	void Win32ConsoleLoggerAdapter::logInformation(const std::string_view channel, const std::string_view log_message) noexcept
	{
		logMessage(channel, log_message, LoggingLevel::information);
	}
	
	void Win32ConsoleLoggerAdapter::logDebug(const std::string_view channel, const std::string_view log_message) noexcept
	{
		logMessage(channel, log_message, LoggingLevel::debug);
	}

	void Win32ConsoleLoggerAdapter::logMessage(const std::string_view channel, const std::string_view log_message,
		const LoggingLevel level) const noexcept
	{
		auto* const handle = GetStdHandle(STD_OUTPUT_HANDLE);
		// Cache the current console attributes to revert afterward
		CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
		GetConsoleScreenBufferInfo(handle, &console_screen_buffer_info);
		const auto previous_console_attribute = console_screen_buffer_info.wAttributes;

		const auto color = s_console_color_map[level];
		SetConsoleTextAttribute(handle, color);
		
		std::cout << getFormattedMessage(channel, log_message, level) << std::endl;

		// Revert back console attributes
		SetConsoleTextAttribute(handle, static_cast<WORD>(previous_console_attribute));
	}

	std::string Win32ConsoleLoggerAdapter::getFormattedTime() const noexcept
	{		
		const auto calender_information = CalenderClock::getCalenderInformation();
		const auto year = calender_information.year;
		const auto month = calender_information.moth;
		const auto day = calender_information.day;
		const auto hour = calender_information.hour;
		const auto minute = calender_information.minute;
		const auto second = calender_information.second;

		const auto date_string {std::to_string(year) + '/' + std::to_string(month) + '/' + std::to_string(day)};
		const auto time_string {std::to_string(hour) + ':' + std::to_string(minute) + ':' + std::to_string(second)};
		
		return '[' + date_string + " - " + time_string + ']';
	}

	std::string Win32ConsoleLoggerAdapter::getFormattedMessage(const std::string_view channel, const std::string_view log_message,
		const LoggingLevel level) const noexcept
	{
		const auto formatted_time = getFormattedTime();
		const auto severity = s_severity_token_map[level];
		return formatted_time + ' ' + channel.data() + " - " + severity + ": " + log_message.data();
	}
}
