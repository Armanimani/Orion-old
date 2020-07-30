#include "Editor/EditorWindow.hpp"
#include "Editor/StyleSheet/StyleSheetManager.hpp"

#include <iostream>
#include <QtWidgets/QScrollBar>

namespace orion::editor
{
	EditorWindow::EditorWindow(QWidget* parent)
		: QMainWindow(parent)
	{
		setStyleSheet(StyleSheetManager::getStylesheet(StyleSheetType::dark));

		ui.setupUi(this);
		initialize();
	}

	void EditorWindow::showEvent(QShowEvent* event)
	{
		showMaximized();
	}

	void EditorWindow::closeEvent(QCloseEvent* event)
	{
		output_pipe.reset();
	}

	void EditorWindow::initialize()
	{
		initializeStreamOutputPipe();
	}
	
	void EditorWindow::initializeStreamOutputPipe() noexcept
	{
		output_pipe = std::make_unique<StreamOutputPipe>(std::cout, ui.text_edit_output);
	}

	void EditorWindow::connectActionsToSlots() const noexcept
	{
		connect(ui.action_Exit, &QAction::triggered, this, &QMainWindow::close);
	}
}
