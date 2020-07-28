#include "Editor/EditorWindow.hpp"
#include "Editor/StyleSheet/StyleSheetManager.hpp"

namespace orion::editor
{
	EditorWindow::EditorWindow(QWidget* parent)
		: QMainWindow(parent)
	{
		this->setStyleSheet(StyleSheetManager::getStylesheet(StyleSheetType::dark));

		ui.setupUi(this);
	}
}