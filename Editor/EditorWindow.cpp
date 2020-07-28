#include "Editor/EditorWindow.hpp"

namespace orion::editor
{
	EditorWindow::EditorWindow(QWidget* parent)
		: QMainWindow(parent)
	{
		ui.setupUi(this);
	}

}