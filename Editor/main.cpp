#include "Editor/EditorWindow.hpp"
#include "Editor/constants.hpp"
#include <QtWidgets/QApplication>
#include <Engine/Logging/ConsoleLogger.hpp>

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	orion::editor::EditorWindow window;
	window.show();

	orion::ConsoleLogger::enableLoggingLevel(orion::LoggingLevel::critical);
	orion::ConsoleLogger::enableLoggingLevel(orion::LoggingLevel::warning);
	orion::ConsoleLogger::enableLoggingLevel(orion::LoggingLevel::information);
	orion::ConsoleLogger::enableLoggingLevel(orion::LoggingLevel::debug);

	orion::ConsoleLogger::logCritical(orion::editor::k_editor_channel, "Critical message example");
	orion::ConsoleLogger::logWarning(orion::editor::k_editor_channel, "Warning message example");
	orion::ConsoleLogger::logInformation(orion::editor::k_editor_channel, "Information message example");
	orion::ConsoleLogger::logDebug(orion::editor::k_editor_channel, "Debug message example");
	
	const auto return_code = application.exec();
	return return_code;
}
