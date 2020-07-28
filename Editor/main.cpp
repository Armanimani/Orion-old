#include "Editor/EditorWindow.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	orion::editor::EditorWindow window;
	window.show();
	
	const auto return_code = application.exec();
	return return_code;
}
