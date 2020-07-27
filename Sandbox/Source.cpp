#include "Engine/Logging/ConsoleLogger.hpp"

int main()
{
	orion::ConsoleLogger::enableLoggingLevel(orion::LoggingLevel::critical);
	orion::ConsoleLogger::enableLoggingLevel(orion::LoggingLevel::warning);
	orion::ConsoleLogger::enableLoggingLevel(orion::LoggingLevel::information);
	orion::ConsoleLogger::enableLoggingLevel(orion::LoggingLevel::debug);

	orion::ConsoleLogger::logCritical("Sandbox", "Critical message example");
	orion::ConsoleLogger::logWarning("Sandbox", "Warning message example");
	orion::ConsoleLogger::logInformation("Sandbox", "Information message example");
	orion::ConsoleLogger::logDebug("Sandbox", "Debug message example");
}